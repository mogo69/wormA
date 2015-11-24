#define NDEBUG

#include "Request.h"

#include <iostream>
using namespace std;

Request::Request()
{
#ifndef NDEBUG
    cout<<"Request was created"<<endl;
#endif
}

Request::~Request()
{
#ifndef NDEBUG
    cout<<"Request was deleted"<<endl;
#endif
}

const Response& Request::process(MYSQL * connect) const
{
    return doProcess(connect);
}

void Request::getFrom(text_iarchive& ia)
{
    doGetFrom(ia);
}

void Request::putInto(text_oarchive& oa) const
{
    doPutInto(oa);
}

