#include "DataStrutures.h"

using namespace PortScanner;

// class ResultItem

ResultItem::ResultItem() {

}

ResultItem::~ResultItem() {

}

ResultItem::ResultItem(const string& _ip, const uint16_t& _port)
    :ip(_ip), port(_port) {

}
