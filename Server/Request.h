#ifndef _REQUEST_H_
#define _REQUEST_H_

using namespace std;
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include <mysql/mysql.h>

class Response;

class Request
{
private:
    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &, const unsigned);

    virtual Response* doProcess(MYSQL *) const = 0;

    Request(const Request&);
    Request& operator=(const Request&);
public:
    Request();
    ~Request();

    virtual void getFrom(text_iarchive&) = 0;
    virtual void putInto(text_oarchive&) const = 0;

    Response* process(MYSQL *) const;
};

template <typename Archive>
void Request::serialize(Archive& ar, const unsigned int version)
{
}

#endif // _REQUEST_H_
