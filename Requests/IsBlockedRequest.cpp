#define NDEBUG

#include <sstream>

#include <string>
using namespace std;

#include "IsBlockedRequest.h"

IsBlockedRequest::IsBlockedRequest(const string& cardNumber):
    Request(),
    _cardNumber(cardNumber)
{
#ifndef NDEBUG
    cout<<"IsBlockedRequest for "<<_cardNumber<<" was created"<<endl;
#endif
}

IsBlockedRequest::~IsBlockedRequest()
{
#ifndef NDEBUG
    cout<<"IsBlockedRequest for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

const Response IsBlockedRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT is_blocked FROM account WHERE card_number = " + _cardNumber).c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(false, "Incorrect card number");
    }
    else
    {
        if(atoi(row[0]))
        {
            return Response(true, "Card is blocked");
        }
        else
        {
            return Response(true, "Card is not blocked");
        }
    }
}

string IsBlockedRequest::doGetSessionKey() const
{
    return "";
}
