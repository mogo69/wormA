#ifndef _GET_BALANCE_REQUEST_H_
#define _GET_BALANCE_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class GetBalanceRequest: public Request
{
public:
    GetBalanceRequest(const string& sessionKey ="");
    virtual ~GetBalanceRequest();
private:
    string _sessionKey;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response doProcess(MYSQL*) const;

    GetBalanceRequest(const Request&);
    GetBalanceRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(GetBalanceRequest)

template <typename Archive>
void GetBalanceRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("sessionKey", _sessionKey);
};

#endif // _GET_BALANCE_REQUEST_H_
