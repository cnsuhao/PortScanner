#ifndef _IOUTPUTER_H_
#define _IOUTPUTER_H_

#include "DataStructures.h"

using namespace PortScanner;

class IOutputer {
public:
    IOutputer();
    virtual void Update(shared_ptr<ResultItem>) = 0;
    virtual ~IOutputer();
};

#endif // _IOUTPUTER_H_
