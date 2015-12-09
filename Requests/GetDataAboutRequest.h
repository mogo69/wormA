#ifndef _GET_DATA_ABOUT_REQUEST_H_
#define _GET_DATA_ABOUT_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class GetDataAboutRequest: public Request
{
public:
    GetDataAboutRequest(const string& sessionKey ="", const string& cardNumber="");
    virtual ~GetDataAboutRequest();
private:
    string _sessionKey;
    string _cardNumber;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    GetDataAboutRequest(const Request&);
    GetDataAboutRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(GetDataAboutRequest)

template <typename Archive>
void GetDataAboutRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("sessionKey", _sessionKey);
    ar & boost::serialization::make_nvp("cardNumber", _cardNumber);
};

#endif // _GET_DATA_ABOUT_REQUEST_H_

