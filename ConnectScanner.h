#ifndef _CONNECT_SCANNER_H_
#define _CONNECT_SCANNER_H_
#include "IScanner.h"
namespace PortScanner {

    class ConnectScanner :
        public IScanner {
    public:
        void Schedule(const std::string ip, uint16_t port);
        //vector<shared_ptr<ResultItem> > GetResult();
        void Run();

        ConnectScanner();
        ~ConnectScanner();
    protected:
        void Notify(shared_ptr<ResultItem>);
        void Attach(shared_ptr<IOutputer> outputer);
        void Detach(shared_ptr<IOutputer> outputer);
    private:
        void HandleSchedule(const shared_ptr<HandleUnit> unit);
        vector<ResultItem*> _rst;
        boost::thread_group _tgrp;
    };

}
#endif //_CONNECT_SCANNER_H_