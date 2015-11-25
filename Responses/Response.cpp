#define NDEBUG

#include "Response.h"

#include <iostream>
using namespace std;

Response::Response()//:_isSuccessful(isSuccessful)
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

/*bool Response::isSuccessful() const
{
    return doIsSuccessful(connect);
}*/

void Response::getFrom(text_iarchive& ia)
{
    doGetFrom(ia);
}

void Response::putInto(text_oarchive& oa) const
{
    doPutInto(oa);
}



