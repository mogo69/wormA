#ifndef _LOGINREQUEST_H_
#define _LOGINREQUEST_H_

#include <string>
using namespace std;

#include "Request.h"
#include "../Responses/Response.h"


class LoginRequest: public Request
{
private:
    string _cardNumber;
    string _PIN;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual const Response& doProcess(MYSQL*) const;

    virtual void doGetFrom(text_iarchive&);
    virtual void doPutInto(text_oarchive&) const;

    LoginRequest(const Request&);
    LoginRequest& operator=(const Request&);
public:
    LoginRequest(const string& cardNumber ="", const string& PIN ="");
    virtual ~LoginRequest();
    void show() const { cout<<"PIN: "<<_PIN<<" card number: "<<_cardNumber<<endl;};
};

template <typename Archive>
void LoginRequest::serialize(Archive &ar, const unsigned int version)
{
    ar & boost::serialization::base_object<Request>(*this);
    ar & _cardNumber;
    ar & _PIN;
};

#endif // _LOGINREQUEST_H_
