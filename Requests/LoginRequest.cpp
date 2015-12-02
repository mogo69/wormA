#define NDEBUG

#include <sstream>

#include <string>
using namespace std;

#include "LoginRequest.h"

string generateRandom(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string res;
    for (int i = 0; i < len; ++i) {
        res += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return res;
}

template < typename T >
string to_string( const T& n )
{
    ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

LoginRequest::LoginRequest(const string& cardNumber, unsigned PIN):
    Request(),
    _cardNumber(cardNumber),
    _PIN(PIN)
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was created"<<endl;
#endif
}

LoginRequest::~LoginRequest()
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

const Response LoginRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT session_key FROM account WHERE card_number = " + _cardNumber + " AND pin = " + to_string(_PIN)).c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
 //       cout<<"Incorrect card number or PIN"<<endl;
        return Response(false, "Incorrect card number or PIN");
    }
    else
    {
        if(row[0] == 0)
        {
 //           cout<<"Session key not set"<<endl;
            string sessionKey = generateRandom(32);
 //           cout<<"Session key generated: "<<sessionKey<<endl;
            mysql_query(connect, ("UPDATE account SET session_key = '" + sessionKey + "' WHERE card_number = " + _cardNumber).c_str());
            return Response(true, sessionKey);
        }
        else
        {
 //           cout<<"Session key is "<<row[0]<<endl;
          return Response(false, "Allready logged in");
        }
    }
    return Response(false, "Something went wrong");
}
