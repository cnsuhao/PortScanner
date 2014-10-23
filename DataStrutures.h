#ifndef _DATA_STRUCTURES_H_
#define _DATA_STRUCTURES_H_
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

namespace PortScanner {
    
    // enum Status

    enum Status {
        Open, Close, TimeOut, Unknown
    };

    // class ResultItem

    class ResultItem {
    public:
        ResultItem();
        ~ResultItem();
        ResultItem(const string& _ip, const uint16_t& _port);


        string ip;
        uint16_t port;
        Status st;
    };

    // class HandleUnit

    class HandleUnit {
    public:
        shared_ptr<tcp::socket> sok;
        shared_ptr<deadline_timer> timer;
        tcp::endpoint ep;
    };

}
#endif // _DATA_STRUCTURES_H_