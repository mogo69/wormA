#ifndef _REQUEST_H_
#define _REQUEST_H_

using namespace std;
#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Request
{
private:
    string _sessionKey;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version);

    Request(const Request&);
    Request& operator=(const Request&);
public:
    Request(const string&);
    ~Request();
};

#endif // _REQUEST_H_
