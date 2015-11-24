#define NDEBUG

#include "ATM.h"

#include <iostream>
using namespace std;

#include <sstream>
std::stringstream ss;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"

void load(Response& res)
{
    text_iarchive ia(ss);
    res.getFrom(ia);
}

string toString(int x)
{
    ss.str("");
    ss<<x;
    string res = ss.str();
    ss.str("");
    return res;
}

//This will be removed after moving to boost sockets
string getSerializedString(const Request& req)
{

    ss.str("");
    text_oarchive oa(ss);
    req.putInto(oa);
    string res = ss.str();
    ss.str("");
    return res;
}

ATM::ATM():
    _sesionKey(""),
    _innerCash(new InnerCash()),
    _connector(new TCPConnector()),
    _stream(_connector->connect("localhost", 9999))
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
    LoginRequest req(cardN, toString(PIN));
    _stream -> send(getSerializedString(req).c_str(), getSerializedString(req).size());
    char answer[255];
    size_t len = _stream->receive(answer, sizeof(answer));
    answer[len] = '\0';

    ss<<answer;

    LoginResponse res;
    load(res);

    cout<<boolalpha;
    cout<<"Successful: "<<res.isSuccessful()<<endl;
    cout<<"Message: "<<res.getMessage()<<endl;

//  If something was received
    return len > 1;
}
