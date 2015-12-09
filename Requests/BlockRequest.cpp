#define NDEBUG

#include <sstream>

#include <string>
using namespace std;

#include "BlockRequest.h"

BlockRequest::BlockRequest(const string& cardNumber):
    Request(),
    _cardNumber(cardNumber)
{
#ifndef NDEBUG
    cout<<"BlockRequest for "<<_cardNumber<<" was created"<<endl;
#endif
}

BlockRequest::~BlockRequest()
{
#ifndef NDEBUG
    cout<<"BlockRequest for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

const Response BlockRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("UPDATE account SET is_blocked = 1 WHERE card_number = " + _cardNumber).c_str());
    return Response(true, "Card was sucessfully blocked");
}

string BlockRequest::doGetSessionKey() const
{
    return "";
}
