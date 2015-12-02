/*#ifndef _LOGOUTREQUEST_H_
#define _LOGOUTREQUEST_H_

#include <string>
using namespace std;

#include "Request.h"
#include "../Responses/Response.h"

class LogoutRequest: public Request
{
public:
    LogoutRequest(const string& sessionKey ="");
    virtual ~LogoutRequest();
private:
    string _sessionKey;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response& doProcess(MYSQL*) const;

    virtual void doGetFrom(text_iarchive&);
    virtual void doPutInto(text_oarchive&) const;

    LogoutRequest(const Request&);
    LogoutRequest& operator=(const Request&);
};

template <typename Archive>
void LogoutRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & boost::serialization::base_object<Request>(*this);
    ar & _sessionKey;
};
#endif // _LOGOUTREQUEST_H_*/
