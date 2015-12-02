#ifndef _WITHDRAW_REQUEST_H_
#define _WITHDRAW_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class WithdrawRequest: public Request
{
public:
    WithdrawRequest(const string& sessionKey ="", const unsigned sum = 0, bool useCreditMoney = false);
    virtual ~WithdrawRequest();
private:
    string _sessionKey;
    unsigned _sum;
    bool _useCreditMoney;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response doProcess(MYSQL*) const;

    WithdrawRequest(const Request&);
    WithdrawRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(WithdrawRequest)

template <typename Archive>
void WithdrawRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("sessionKey", _sessionKey);
    ar & boost::serialization::make_nvp("sum", _sum);
    ar & boost::serialization::make_nvp("useCreditMoney", _useCreditMoney);
};

#endif // _WITHDRAW_REQUEST_H_

