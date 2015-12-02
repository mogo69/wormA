#include "GetBalanceRequest.h"

GetBalanceRequest::GetBalanceRequest(const string& sessionKey):
    Request(),
    _sessionKey(sessionKey)
{

}

GetBalanceRequest::~GetBalanceRequest()
{

}

const Response GetBalanceRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT balance FROM account WHERE session_key = '" + _sessionKey + "'").c_str());
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(false, "You session has been expired");
    }
    return Response(true, row[0]);
}
