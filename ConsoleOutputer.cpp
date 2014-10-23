#include "DataStructures.h"
#include "ConsoleOutputer.h"

using namespace std;

ConsoleOutputer::ConsoleOutputer() {
}


ConsoleOutputer::~ConsoleOutputer() {
    //std::cout << "~ConsoleOutputer" << std::endl;
}

void
ConsoleOutputer::Update(shared_ptr<ResultItem> pItem) {
    cout << pItem->ip << ":" << pItem->port << " is " << ([] (const PortScanner::Status &st) {
        if (st == Open) {
            return "Open";
        }
        else if (st == Close || st == TimeOut) {
            return "Closed Or Timed Out";
        }
        else {// if (st == Unknown) {
            return "Unknown";
        }
    })(pItem->st) << endl;
}
