#define NDEBUG

#include "Response.h"

#include <iostream>
using namespace std;

Response::Response(const bool wasSuccessful, const string& message):
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




