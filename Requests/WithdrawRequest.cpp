#include "WithdrawRequest.h"
#include <sstream>

#include <string>
using namespace std;

WithdrawRequest::WithdrawRequest(const string& sessionKey, const unsigned sum, bool useCreditMoney):
    Request(),
    _sessionKey(sessionKey),
    _sum(sum),
    _useCreditMoney(useCreditMoney)
{

}

WithdrawRequest::~WithdrawRequest()
{

}

template < typename T >
string to_string( const T& n )
{
    ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

const Response WithdrawRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT balance, credit_balance FROM account WHERE session_key = '" + _sessionKey + "'").c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(false, "You session has been expired");
    }
    double balance = atof(row[0]);
    double credit_balance = atof(row[1]);
    if(balance < _sum && !_useCreditMoney) return Response(false, "You haven't such amount of money.");
    if(_useCreditMoney && abs(balance-_sum) > credit_balance) return Response(false, "Your credit balance is too small.");
    balance -= _sum;
    mysql_query(connect, ("UPDATE account SET balance = '" + to_string(balance) + "' WHERE session_key = '" + _sessionKey + "'").c_str());
    return Response(true, "Withdraw was successful.");
}

string WithdrawRequest::doGetSessionKey() const
{
    return _sessionKey;
}



