#include "ConnectScanner.h"
#include "ConsoleOutputer.h"
using namespace PortScanner;

ConnectScanner::ConnectScanner() {
    //_rst = new vector<ResultItem*>();

    Attach(shared_ptr<IOutputer>(new ConsoleOutputer));
}

ConnectScanner::~ConnectScanner() {

}

void
ConnectScanner::Schedule(const std::string ip, uint16_t port) {
    auto unit = std::shared_ptr<HandleUnit>(new HandleUnit);
    //unit->cb = cb;
    unit->ep = tcp::endpoint(address_v4::from_string(ip), port);
    unit->sok = std::shared_ptr<tcp::socket>(new tcp::socket(_io));
    unit->timer = std::shared_ptr<deadline_timer>(new deadline_timer(_io));
    //unit->st = Unknown;
    //
    _tgrp.add_thread(new boost::thread(
        boost::bind(&ConnectScanner::HandleSchedule, this, unit)));
}

void
ConnectScanner::HandleSchedule(const std::shared_ptr<HandleUnit> unit) {
    boost::system::error_code ec;
    //timer start
    deadline_timer tm(_io);
    tm.expires_from_now(boost::posix_time::seconds(2));
    tm.async_wait([&] (const boost::system::error_code &ec) {
        //cout << unit->ep.address().to_string() << " is timed out." << endl;
        unit->sok->cancel();
        unit->sok->close();
    });
    //connect
    unit->sok->connect(unit->ep, ec);//block here
    //get result
    auto item = shared_ptr<ResultItem>(new ResultItem(
        unit->ep.address().to_string(),
        unit->ep.port()
        ));

    if (unit->sok->is_open() && !ec) {
        unit->sok->close();
        item->st = Open;
    }
    else {
        item->st = Close;
    }
    _rst.push_back(item.get());
    Notify(item);
}

void
ConnectScanner::Run() {
    _tgrp.join_all();
}

//vector<std::shared_ptr<ResultItem> >
//ConnectScanner::GetResult() {
//    return *_rst;
//}

void
ConnectScanner::Notify(shared_ptr<ResultItem> pItem) {
    for (auto outputer : _outputers) {
        _mutex.lock();
        outputer->Update(pItem);
        _mutex.unlock();
    }
}

void
ConnectScanner::Attach(shared_ptr<IOutputer> outputer) {
    _outputers.push_back(outputer);
}

void
ConnectScanner::Detach(shared_ptr<IOutputer> outputer) {
    _outputers.remove(outputer);
}
