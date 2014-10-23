#ifndef _CONSOLE_OUTPUTER_H_
#define _CONSOLE_OUTPUTER_H_
#include "IOutputer.h"


class ConsoleOutputer :
    public IOutputer {
public:
    void Update(shared_ptr<ResultItem> pItem);
    ConsoleOutputer();
    ~ConsoleOutputer();
};

#endif // _CONSOLE_OUTPUTER_H_