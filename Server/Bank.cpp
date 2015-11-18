#include "Bank.h"
#include "TCPStream.h"
#include "TCPAcceptor.h"

#include <iostream>
using namespace std;

const string Bank::SQL_GET_ALL_ACCOUNTS= "SELECT * FROM account";

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
    TCPStream* stream(0);
    TCPAcceptor* acceptor = new TCPAcceptor(port, host.c_str());
    if (acceptor->start() == 0) {
        cout<<"TCP Server successfuly started at host "<<host<<" on port "<<port<<endl;
        while (1) {
            stream = acceptor->accept();
            if (stream != NULL) {
                size_t len;
                char line[256];
                while ((len = stream->receive(line, sizeof(line))) > 0) {
                    line[len] = 0;
                    cout<<"Received: "<<line<<endl;
                    stream->send("random text", sizeof("random text"));
                }
                delete stream;
            }
        }
    }
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


