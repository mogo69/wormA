/*#define NDEBUG

#include "LogoutRequest.h"

LogoutRequest::LogoutRequest(const string& sessionKey):
    Request(),
    _sessionKey(sessionKey)
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was created"<<endl;
#endif
}

LogoutRequest::~LogoutRequest()
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

const Response& LogoutRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("UPDATE account SET session_key = NULL WHERE session_key = " + _sessionKey).c_str());
    return *(new Response(true, "Successfuly loged out"));
}

void LogoutRequest::doGetFrom(text_iarchive& ia)
{
    ia.register_type<LogoutRequest>();
    ia >> *this;
}

void LogoutRequest::doPutInto(text_oarchive& oa) const
{
    oa.register_type<LogoutRequest>();
    oa << *this;
}
*/

