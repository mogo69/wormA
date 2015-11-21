#include "Request.h"

#include <iostream>
using namespace std;

Request::Request(const string& sessionKey):
    _sessionKey(sessionKey)
{
#ifndef NDEBUG
    cout<<"Request with session key "<<_sessionKey<<" was created"<<endl;
#endif
}

Request::~Request()
{
#ifndef NDEBUG
    cout<<"Request with session key "<<_sessionKey<<" was deleted"<<endl;
#endif
}

template<class Archive>
void Request::serialize(Archive & ar, const unsigned int version)
{
    ar & _sessionKey;
}
