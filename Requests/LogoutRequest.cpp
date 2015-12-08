#define NDEBUG

#include <sstream>

#include <string>
using namespace std;

#include "LogoutRequest.h"

LogoutRequest::LogoutRequest(const string& sessionKey):
    Request(),
    _sessionKey(sessionKey)
{
#ifndef NDEBUG
    cout<<"Logut Request for "<<_sessionKey<<" was created"<<endl;
#endif
}

LogoutRequest::~LogoutRequest()
{
#ifndef NDEBUG
    cout<<"Logout Request for "<<_sessionKey<<" was deleted"<<endl;
#endif
}

const Response LogoutRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("UPDATE account SET session_key = NULL WHERE session_key = '" + _sessionKey + "'").c_str());
    return Response(true, "You have loged out successfuly");
}

string LogoutRequest::doGetSessionKey() const
{
    return _sessionKey;
}
