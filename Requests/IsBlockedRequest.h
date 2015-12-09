#ifndef _IS_BLOCKED_REQUEST_H_
#define _IS_BLOCKED_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class IsBlockedRequest: public Request
{
public:
    IsBlockedRequest(const string& cardNumber ="");
    virtual ~IsBlockedRequest();
private:
    string _cardNumber;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    IsBlockedRequest(const Request&);
    IsBlockedRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(IsBlockedRequest)

template <typename Archive>
void IsBlockedRequest::serialize(Archive &ar, const unsigned version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("cardNumber", _cardNumber);
};

#endif // _IS_BLOCKED_REQUEST_H_
