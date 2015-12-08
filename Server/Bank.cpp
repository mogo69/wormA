#define NDEBUG

#include "Bank.h"

#include <iostream>
using namespace std;

#include <boost/asio.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "../Requests/Request.h"
#include "../Requests/LoginRequest.h"
#include "../Requests/LogoutRequest.h"
#include "../Requests/GetBalanceRequest.h"
#include "../Requests/WithdrawRequest.h"
#include "../Requests/GetAdvertRequest.h"
#include "../Requests/GetDataAboutRequest.h"

#include "../Responses/Response.h"

BOOST_CLASS_EXPORT_GUID(Request, "request")
BOOST_CLASS_EXPORT_GUID(LoginRequest, "login_request")
BOOST_CLASS_EXPORT_GUID(LogoutRequest, "logout_request")
BOOST_CLASS_EXPORT_GUID(GetBalanceRequest, "get_balance_request")
BOOST_CLASS_EXPORT_GUID(WithdrawRequest, "withdraw_request")
BOOST_CLASS_EXPORT_GUID(GetAdvertRequest, "get_advert_request")
BOOST_CLASS_EXPORT_GUID(GetDataAboutRequest, "get_data_about_request")

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

    cout<<"TCP Server successfuly started at host "<<host<<" on port "<<port<<endl;

    while (true)
    {
        boost::asio::ip::tcp::socket socket( io_service );
        acceptor.accept( socket );

        size_t header;
        boost::asio::read(socket, boost::asio::buffer(&header, sizeof(header)));

        boost::asio::streambuf buf;
        boost::asio::read(socket, buf.prepare( header ));
        buf.commit( header );

        istream is( &buf );
        boost::archive::text_iarchive iar( is );

        boost::shared_ptr<Request> req;
        iar & boost::serialization::make_nvp("item", req);

        Response resp;

        if(req->getSessionKey() == "")
        {
            try
            {
                //dynamic_cast<boost::shared_ptr<LoginRequest>>(req));
                try
                {
                     resp = req->process(connect);
                }
                catch(...)
                {
                    resp = Response(false, "Database problem");
                }

            }
            catch(...)
            {
                resp = Response(false, "You do not use session key");
            }

        }
        else
        {
            mysql_query(connect, ("SELECT session_key FROM account WHERE session_key = '" + req->getSessionKey() + "'").c_str());
            MYSQL_ROW row = mysql_fetch_row(mysql_store_result(connect));

            if(row == 0)
            {
                resp = Response(false, "You, son of a bitch, you can't hack our system!!!");
            }
            else
            {
                try
                {
                     resp = req->process(connect);
                }
                catch(...)
                {
                    resp = Response(false, "Database problem");
                }
            }
        }

        std::ostream os( &buf );
        boost::archive::text_oarchive oar( os );
        oar & resp;

        header = buf.size();

        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back( boost::asio::buffer(&header, sizeof(header)) );
        buffers.push_back( buf.data() );
        boost::asio::write(socket, buffers);
    }
    mysql_close(connect);
}

Bank::~Bank()
{
#ifndef NDEBUG
    cout<<"Bank was successfully deleted"<<endl;
#endif
}

Bank& Bank::getInstance(const string& dbHost,
        const string& dbName,
        const string& dbUser,
        const string& dbPass,
        const string& host,
        size_t port)
{
    static Bank instance(dbHost, dbName, dbUser, dbPass, host, port);
    return instance;
}


