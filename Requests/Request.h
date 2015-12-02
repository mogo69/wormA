#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <mysql/mysql.h>

#include "../Responses/Response.h"

class Request
{
public:
    Request();
    virtual ~Request();

    const Response process(MYSQL *) const;
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &, const unsigned);

    virtual const Response doProcess(MYSQL *) const = 0;

    Request(const Request&);
    Request& operator=(const Request&);
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Request)
BOOST_SERIALIZATION_SHARED_PTR(Request)

template <typename Archive>
void Request::serialize(Archive& ar, const unsigned int version)
{
}

#endif // _REQUEST_H_
