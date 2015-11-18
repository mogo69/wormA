#include <iostream>
using namespace std;
#include <sstream>

#include "ATM.h"

#include "TCPConnector.h"
#include "TCPStream.h"


ATM::ATM():
    _sesionKey(""),
    _innerCash(new InnerCash()),
    _connector(new TCPConnector()),
    _stream(_connector->connect("localhost", 8080))
{
#ifndef NDEBUG
    cout << "ATM created." << endl;
    if (_stream) cout<<"Connection to server established"<<endl;
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

bool ATM::logIn(const string cardN, const size_t PIN)
{
    string message ("login ");
    message += cardN;
    message += " ";
    ostringstream ss;
    ss<<PIN;
    message += ss.str();
    _stream->send(message.c_str(), message.size());
    size_t len(0);
    char answer[256];
    len = _stream->receive(answer, sizeof(answer));
    answer[len] = '\0';
    return len > 1;
}
