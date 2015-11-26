#define NDEBUG

#include "Response.h"

#include <iostream>
using namespace std;

Response::Response(const bool wasSuccessful, const string message):
    _wasSuccessful(wasSuccessful), _message(message)
{
#ifndef NDEBUG
    cout<<"Response was created"<<endl;
#endif
}

Response::~Response()
{
#ifndef NDEBUG
    cout<<"Response was deleted"<<endl;
#endif
}

void Response::getFrom(text_iarchive& ia)
{
    ia.register_type<Response>();
    ia >> *this;
}

void Response::putInto(text_oarchive& oa) const
{
    oa.register_type<Response>();
    oa << *this;
}



