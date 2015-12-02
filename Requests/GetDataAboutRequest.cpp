#define NDEBUG

#include <sstream>

#include <string>
using namespace std;

#include "GetDataAboutRequest.h"

GetDataAboutRequest::GetDataAboutRequest(const string& sessionKey, const string cardNumber):
    Request(),
    _sessionKey(sessionKey),
    _cardNumber(cardNumber)
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was created"<<endl;
#endif
}

GetDataAboutRequest::~GetDataAboutRequest()
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

const Response GetDataAboutRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT owner FROM account WHERE card_number = '" + _cardNumber+"'").c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(true, "No such credit card.");
    }
    return Response(true, row[0]);
}

