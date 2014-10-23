#include <iostream>
#include <vector>
#include <boost/program_options.hpp>

#include "ConnectScanner.h"
using namespace std;
using namespace boost::program_options;
using namespace boost::asio::ip;
using namespace PortScanner;

int main(int argc, char *argv[]) {
    //argc = 7;
    //argv[1] = "-s";
    //argv[2] = "114.215.136.1";
    //argv[3] = "-e";
    //argv[4] = "114.215.136.30";
    //argv[5] = "-p";
    //argv[6] = "80";

    boost::program_options::options_description opts("PortScanner Usage");
    opts.add_options()
        ("help,h", "show help information")
        ("start,s", value<string>(), "ip address which starts from")
        ("end,e", value<string>(), "ip address which ends with")
        ("port,p", value<uint16_t>()->default_value(80), "which port will be scaned");

    variables_map vm;
    try {
        store(parse_command_line(argc, argv, opts), vm);
    } catch (exception &ex) {
        cout << ex.what() << endl;
        return 0;
    }
    notify(vm);

    if (vm.count("help")) {
        cout << opts << endl;
        return 0;
    }

    if (!vm.count("start")) {
        cout << "error: --start or -s parameter must be set." << endl;
        cout << opts << endl;
        return 0;
    }

    if (!vm.count("end")) {
        cout << "error: --end or -e parameter must be set." << endl;
        cout << opts << endl;
        return 0;
    }

    try {
        shared_ptr<IScanner> connectScanner(new ConnectScanner());
        unsigned long start = address_v4::from_string(vm["start"].as<string>()).to_ulong();
        unsigned long end = address_v4::from_string(vm["end"].as<string>()).to_ulong();

        //cout << "start : end = " << start << " : " << end << endl;
        if (start > end) {
            std::swap(start, end);
        }

        for (unsigned long i = start; i <= end; i++) {
            connectScanner->Schedule(address_v4(i).to_string(), vm["port"].as<uint16_t>());
        }
        connectScanner->Run();

    } catch (exception& ex) {
        cout << ex.what() << endl;
        return 0;
    }

    return 0;
}
