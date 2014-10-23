#include "IScanner.h"
using namespace PortScanner;

// class IScanner

io_service IScanner::_io;
boost::mutex IScanner::_mutex;

IScanner::IScanner() {

}

IScanner::~IScanner() {
    //smart pointer calls destruct function automatically
    //std::cout << "~Scanner" << std::endl;
}

io_service* IScanner::IOService()const {
    return &_io;
}
