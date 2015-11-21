#ifndef _LOGINREQUEST_H_
#define _LOGINREQUEST_H_

#include "Request.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

class LoginRequest: public Request
{
private:
    string _cardNumber;
    string _PIN;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual Response* doProcess(MYSQL*) const;

    LoginRequest(const Request&);
    LoginRequest& operator=(const Request&);
public:
    LoginRequest(const string& cardNumber ="", const string& PIN ="");
    ~LoginRequest();
    virtual void getFrom(text_iarchive&);
    virtual void putInto(text_oarchive&) const;
};

template <typename Archive>
void LoginRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & boost::serialization::base_object<Request>(*this);
    ar & _cardNumber;
    ar & _PIN;
};

#endif // _LOGINREQUEST_H_
