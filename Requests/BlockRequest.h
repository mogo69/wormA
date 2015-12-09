#ifndef _BLOCK_REQUEST_H_
#define _BLOCK_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class BlockRequest: public Request
{
public:
    BlockRequest(const string& cardNumber ="");
    virtual ~BlockRequest();
private:
    string _cardNumber;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    BlockRequest(const Request&);
    BlockRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(BlockRequest)

template <typename Archive>
void BlockRequest::serialize(Archive &ar, const unsigned version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
    ar & boost::serialization::make_nvp("cardNumber", _cardNumber);
};

#endif // _BLOCK_REQUEST_H_
