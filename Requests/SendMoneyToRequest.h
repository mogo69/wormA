#ifndef _SEND_MONEY_TO_REQUEST_H_
#define _SEND_MONEY_TO_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class SendMoneyToRequest: public Request
{
public:
    SendMoneyToRequest(const string& sessionKey ="", const unsigned sum = 0, const string& cardNumber ="");
    virtual ~SendMoneyToRequest();
private:
    string _sessionKey;
    unsigned _sum;
    string _cardNumber;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    SendMoneyToRequest(const Request&);
    SendMoneyToRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(SendMoneyToRequest)

template <typename Archive>
void SendMoneyToRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("sessionKey", _sessionKey);
    ar & boost::serialization::make_nvp("sum", _sum);
    ar & boost::serialization::make_nvp("cardNumber", _cardNumber);
};

#endif // _SEND_MONEY_TO_REQUEST_H_


