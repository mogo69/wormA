#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include <mysql/mysql.h>
#include <iostream>
using namespace std;

class Response
{
private:
    //bool _isSuccessful;
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &, const unsigned);

    //virtual bool doIsSuccessful() const = 0;

    virtual void doGetFrom(text_iarchive&) = 0;
    virtual void doPutInto(text_oarchive&) const = 0;

    Response(const Response&);
    Response& operator=(const Response&);

public:
    Response(/*bool isSuccessful*/);
    virtual ~Response();
    //bool isSuccessful() const;

    void getFrom(text_iarchive&);
    void putInto(text_oarchive&) const;
};

template <typename Archive>
void Response::serialize(Archive& ar, const unsigned int version)
{
    //ar & _isSuccessful;
}

#endif // _RESPONSE_H_
