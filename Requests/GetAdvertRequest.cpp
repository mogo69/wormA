#include "GetAdvertRequest.h"

GetAdvertRequest::GetAdvertRequest(const string& sessionKey):
    _sessionKey(sessionKey)
{

}

GetAdvertRequest::~GetAdvertRequest()
{

}

const Response GetAdvertRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, "SELECT content FROM commercial ORDER BY RAND() LIMIT 1");
    MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));
    if(row == 0)
    {
        return Response(false, "");
    }
    return Response(true, row[0]);
}

string GetAdvertRequest::doGetSessionKey() const
{
    return _sessionKey;
}
