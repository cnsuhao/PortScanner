#ifndef _ISCANNER_H_
#define _ISCANNER_H_
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "DataStructures.h"
#include "IOutputer.h"
//Scanner Interface
using namespace boost::system;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace std;

namespace PortScanner {

    // class IScanner

    class IScanner {
    public:
        virtual void Schedule(const string ip, uint16_t port) = 0;
        virtual void Run() = 0;
        //virtual vector<shared_ptr<ResultItem> > GetResult() = 0;
        //Observer pattern
        virtual void Notify(shared_ptr<ResultItem>) = 0;
        virtual void Attach(shared_ptr<IOutputer> outputer) = 0;
        virtual void Detach(shared_ptr<IOutputer> outputer) = 0;

        virtual ~IScanner();
        io_service* IOService()const;
    protected:
        IScanner();
        virtual void HandleSchedule(const shared_ptr<HandleUnit> unit) = 0;
        static io_service _io;
        static boost::mutex _mutex;
        list<shared_ptr<IOutputer> > _outputers;
    private:
        
    };

}

#endif //_ISCANNER_H_
