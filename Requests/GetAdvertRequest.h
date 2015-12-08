#ifndef _GET_ADVERT_REQUEST_H_
#define _GET_ADVERT_REQUEST_H_

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>
using namespace std;

#include "Request.h"

class GetAdvertRequest: public Request
{
public:
    GetAdvertRequest(const string& sessionKey="");
    virtual ~GetAdvertRequest();
private:
    string _sessionKey;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response doProcess(MYSQL*) const;
    virtual string doGetSessionKey() const;

    GetAdvertRequest(const Request&);
    GetAdvertRequest& operator=(const Request&);
};

BOOST_SERIALIZATION_SHARED_PTR(GetAdvertRequest)

template <typename Archive>
void GetAdvertRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Request);
};

#endif // _GET_ADVERT_REQUEST_H_
