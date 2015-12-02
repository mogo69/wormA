#include "GetAdvertRequest.h"

GetAdvertRequest::GetAdvertRequest()
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
