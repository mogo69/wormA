#ifndef _LOGOUTREQUEST_H_
#define _LOGOUTREQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

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

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    LogoutRequest(const Request&);
    LogoutRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(LogoutRequest)

template <typename Archive>
void LogoutRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("sessionKey", _sessionKey);
};
#endif // _LOGINREQUEST_H_
