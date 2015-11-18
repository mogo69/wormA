#include "ATM.h"

#include <iostream>

ATM::ATM():
    _sesionKey(""),
    _innerCash(new InnerCash())
{
#ifndef NDEBUG
    cout << "ATM created." << endl;
#endif
}
ATM::~ATM()
{
#ifndef NDEBUG
    cout << "ATM deleated." << endl;
#endif
    delete _innerCash;
}

ATM& ATM::getInstance()
{
    static ATM instance;
    return instance;
}

ATM::InnerCash::InnerCash():
    _pockets(new Pocket[4])
{
#ifndef NDEBUG
    cout << _pockets->_quantity << endl;
#endif

}
ATM::InnerCash::~InnerCash()
{
    delete [] _pockets;
}
