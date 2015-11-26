/*#define NDEBUG

#include "LoginResponse.h"

LoginResponse::LoginResponse(const bool isSuccessful, const string& message):
      Response(),
      _isSuccessful(isSuccessful),
      _message(message)
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was created"<<endl;
#endif
}

LoginResponse::~LoginResponse()
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

bool LoginResponse::isSuccessful() const
{
    return _isSuccessful;
}

string LoginResponse::getMessage() const
{
    return _message;
}

void LoginResponse::doGetFrom(text_iarchive& ia)
{
    ia.register_type<LoginResponse>();
    ia >> *this;
}

void LoginResponse::doPutInto(text_oarchive& oa) const
{
    oa.register_type<LoginResponse>();
    oa << *this;
}*/
