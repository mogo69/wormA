#include "LoginRequest.h"

LoginRequest::LoginRequest(const string& cardNumber, const string& PIN):
    Request(),
    _cardNumber(cardNumber),
    _PIN(PIN)
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was created"<<endl;
#endif
}

LoginRequest::~LoginRequest()
{
#ifndef NDEBUG
    cout<<"Login Request for "<<_cardNumber<<" was deleted"<<endl;
#endif
}

Response* LoginRequest::doProcess(MYSQL* connect) const
{
    mysql_query(connect, ("SELECT name FROM user WHERE card_number = " + _cardNumber + " AND pin = " + _PIN).c_str());
    return 0;
}

void LoginRequest::getFrom(text_iarchive& ia)
{
    ia.register_type<LoginRequest>();
    ia >> *this;
}

void LoginRequest::putInto(text_oarchive& oa) const
{
    oa.register_type<LoginRequest>();
    oa << *this;
}

