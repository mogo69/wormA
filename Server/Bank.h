/*
 * Bank.h
 * Author: Volodymyr Kuryliak
 *
 */

#ifndef _BANK_H_
#define _BANK_H_

#include <string>
using namespace std;

#include <mysql/mysql.h>

class Bank
{
private:
    string _dbHost;
    string _dbName;
    string _dbUser;
    string _dbPass;
    string _host;
    size_t _port;

    Bank(const string& dbHost = "sql4.freesqldatabase.com",
        const string& dbName = "sql497472",
        const string& dbUser = "sql497472",
        const string& dbPass = "dmLXwQJbZz",
        const string& host = "localhost",
        size_t port = 9999);

    bool takeMoney(size_t cardNumber, size_t amount, bool useCreditMoney = false);
    string getData(size_t cardNumber);
    bool sendMoney(size_t from, size_t to);
    double getBalance(size_t cardNumber);
    string getAdvert();
    bool changePIN(size_t cardNumber, size_t newPIN);
    bool checkAuth(size_t cardNumber, size_t PIN);
    bool isBlocked(size_t cardNumber);

//  Not used, that's why not implemented
    Bank(const Bank&);
    Bank& operator=(const Bank&);

public:
    ~Bank();
    static Bank& getInstance();
};

#endif // _BANK_H_
