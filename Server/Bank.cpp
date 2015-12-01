#define NDEBUG

#include "Bank.h"

#include <iostream>
using namespace std;

#include <sstream>
std::stringstream ss;

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;

#include "../Connection/TCPStream.h"
#include "../Connection/TCPAcceptor.h"

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"
#include "../Requests/LogoutRequest.h"

#include "../Responses/Response.h"

void load(Request& req)
{
    text_iarchive ia(ss);
    req.getFrom(ia);
}

string getSerializedString(const Response& response)
{
    ss.str("");

    text_oarchive oa(ss);
    response.putInto(oa);
    string res = ss.str();
    ss.str("");
    return res;
}

Bank::Bank(const string& dbHost,
        const string& dbName,
        const string& dbUser,
        const string& dbPass,
        const string& host,
        size_t port):
        _dbHost(dbHost),
        _dbName(dbName),
        _dbUser(dbUser),
        _dbPass(dbPass),
        _host(host),
        _port(port)
{
#ifndef NDEBUG
    cout<<"Bank was successfully created"<<endl;
#endif
    MYSQL* connect;
    connect = mysql_init(NULL);
    if (!connect)
    {
        cout<<"MySQL Initialization failed";
    }
    connect=mysql_real_connect(connect, _dbHost.c_str(), _dbUser.c_str(), _dbPass.c_str(), _dbName.c_str(), 0, NULL, 0);
    if (connect)
    {
        cout<<"Database connection succeeded"<<endl;
    }
    else
    {
        cout<<"Database connection failed"<<endl;
    }
    TCPStream* stream(0);
    TCPAcceptor* acceptor = new TCPAcceptor(port, host.c_str());
    if (acceptor->start() == 0)
    {
        cout<<"TCP Server successfuly started at host "<<host<<" on port "<<port<<endl;
        while (1)
        {
            stream = acceptor->accept();
            if (stream != 0)
            {
                size_t len;
                char line[256];
                while ((len = stream->receive(line, sizeof(line))) > 0)
                {
                    line[len] = 0;
 //                   cout<<"Received: "<<line<<endl;
                    ss<<line;

                    Request* req = new LoginRequest();
                    load(*req);


                   const Response& res=  req->process(connect);
                   stream -> send(getSerializedString(res).c_str(), getSerializedString(res).size());
//                  Not the best solution
                    delete &res;
                }
                delete stream;
            }
        }
    }
    mysql_close(connect);
}

Bank::~Bank()
{
#ifndef NDEBUG
    cout<<"Bank was successfully deleted"<<endl;
#endif
}

Bank& Bank::getInstance()
{
    static Bank instance;
    return instance;
}


