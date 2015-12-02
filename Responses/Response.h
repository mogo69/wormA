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
public:
    Response(const bool wasSuccessful = false, const string& message = "");
    Response(const Response&);
    Response& operator=(const Response&);
    virtual ~Response();

    inline bool wasSuccessful() const { return _wasSuccessful;}
    inline string getMessage() const  { return _message;      }

private:
    bool _wasSuccessful;
    string _message;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive &, const unsigned);
};

template <typename Archive>
void Response::serialize(Archive& ar, const unsigned int version)
{
     ar & _wasSuccessful;
     ar & _message;
}

#endif // _RESPONSE_H_
