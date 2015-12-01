#define NDEBUG

#include "Bank.h"

#include <iostream>
using namespace std;

#include <boost/asio.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace boost::archive;

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"

#include "../Responses/Response.h"
#include "../Responses/LoginResponse.h"

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
    connect=mysql_real_connect(connect, _dbHost.c_str(), _dbUser.c_str(), _dbPass.c_str(), _dbName.c_str(), 0, 0, 0);
    if (connect)
    {
        cout<<"Database connection succeeded"<<endl;
    }
    else
    {
        cout<<"Database connection failed"<<endl;
    }

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"),_port));

    boost::asio::ip::tcp::socket socket( io_service );

    cout<<"TCP Server successfuly started at host "<<host<<" on port "<<port<<endl;

    while (true)
    {
        acceptor.accept( socket );
        size_t header;
        boost::asio::read(socket, boost::asio::buffer(&header, sizeof(header)));

        boost::asio::streambuf buf;
        const size_t rc = boost::asio::read(socket, buf.prepare( header ));
        buf.commit( header );

        istream is( &buf );
        boost::archive::text_iarchive ar( is );

        LoginRequest req;
        ar & req;
        req.show();
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


