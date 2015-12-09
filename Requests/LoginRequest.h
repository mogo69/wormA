#ifndef _LOGINREQUEST_H_
#define _LOGINREQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class LoginRequest: public Request
{
public:
    LoginRequest(const string& cardNumber ="",  const unsigned PIN = 0);
    virtual ~LoginRequest();
private:
    string _cardNumber;
    unsigned _PIN;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    LoginRequest(const Request&);
    LoginRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(LoginRequest)

template <typename Archive>
void LoginRequest::serialize(Archive &ar, const unsigned version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("cardNumber", _cardNumber);
    ar & boost::serialization::make_nvp("PIN", _PIN);
};
#endif // _LOGINREQUEST_H_
