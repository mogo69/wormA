#include "SendMoneyToRequest.h"
#include <sstream>

#include <string>
using namespace std;

SendMoneyToRequest::SendMoneyToRequest(const string& sessionKey, const unsigned sum, const string& cardNumber):
    Request(),
    _sessionKey(sessionKey),
    _sum(sum),
    _cardNumber(cardNumber)
{

}

SendMoneyToRequest::~SendMoneyToRequest()
{

}

template < typename T >
string to_string( const T& n )
{
    ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

const Response SendMoneyToRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT balance, card_number FROM account WHERE session_key = '" + _sessionKey + "'").c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(false, "You session has been expired");
    }
    double balance = atof(row[0]);

    if(row[1] == _cardNumber)
    {
        return Response(true, "This is the same card");
    }

    if(balance < _sum) return Response(false, "You haven't such amount of money.");

    mysql_query(connect, ("SELECT balance FROM account WHERE card_number = '" + _cardNumber + "'").c_str());
    MYSQL_ROW row2 = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0) return Response(false, "No such card number");

    double balance2 = atof(row2[0]);
    balance2 += _sum;
    balance -= _sum;
    mysql_query(connect, ("UPDATE account SET balance = '" + to_string(balance) + "' WHERE session_key = '" + _sessionKey + "'").c_str());
    mysql_query(connect, ("UPDATE account SET balance = '" + to_string(balance2) + "' WHERE card_number = '" + _cardNumber + "'").c_str());
    return Response(true, "Transfer was successful.");
}

string SendMoneyToRequest::doGetSessionKey() const
{
    return _sessionKey;
}




