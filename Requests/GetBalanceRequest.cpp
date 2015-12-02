#include "GetBalanceRequest.h"

GetBalanceRequest::GetBalanceRequest(const string& sessionKey):
    _sessionKey(sessionKey)
{

}

GetBalanceRequest::~GetBalanceRequest()
{

}

const Response GetBalanceRequest::doProcess(MYSQL*) const
{
    return Response();
}
