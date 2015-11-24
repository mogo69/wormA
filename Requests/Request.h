#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include <mysql/mysql.h>

#include "../Responses/Response.h"

class Request
{
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &, const unsigned);

    virtual const Response& doProcess(MYSQL *) const = 0;

    virtual void doGetFrom(text_iarchive&) = 0;
    virtual void doPutInto(text_oarchive&) const = 0;

    Request(const Request&);
    Request& operator=(const Request&);
public:
    Request();
    virtual ~Request();

    const Response& process(MYSQL *) const;

    void getFrom(text_iarchive&);
    void putInto(text_oarchive&) const;
};

template <typename Archive>
void Request::serialize(Archive& ar, const unsigned int version)
{
}

#endif // _REQUEST_H_
