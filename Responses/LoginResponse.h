/*#ifndef _LOGINRESPONSE_H_
#define _LOGINRESPONSE_H_

#include <string>
using namespace std;

#include "Response.h"

class LoginResponse: public Response
{
private:
    bool _isSuccessful;
    string _message;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int version);

    virtual void doGetFrom(text_iarchive&);
    virtual void doPutInto(text_oarchive&) const;

    LoginResponse(const LoginResponse&);
    LoginResponse& operator=(const LoginResponse&);
public:
    LoginResponse(const bool isSuccessful = false, const string& message ="");
    virtual ~LoginResponse();

    bool isSuccessful() const;
    string getMessage() const;
};

template <typename Archive>
void LoginResponse::serialize(Archive &ar, const unsigned int version)
{
    ar & boost::serialization::base_object<Response>(*this);
    ar & _isSuccessful;
    ar & _message;
    //ar & _PIN;
};

#endif // _LOGINRESPONSE_H_*/
