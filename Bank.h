/*
 * Bank.h
 * Author: Volodymyr Kuryliak
 *
 */


#ifndef _BANK_H_
#define _BANK_H_

#include <string>
using namespace std;

// Dummy forwarded declatation,
// will be removed later;
class Transaction;

class Bank
{
private:

    static const string SQL_GET_ALL_THE_FUCKING_ACCOUNTS;

    string _db_host;
    string _db_name;
    string _db_user;
    string _db_pass;
    string _host;
    size_t _port;

    Bank(const string& dbHost,
        const string& dbName,
        const string& dbUser,
        const string& dbPass,
        const string& host = "localhost",
        size_t port = 8080);

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
    Bank& getInstance();
    string process(const Transaction&);
};

#endif // _BANK_H_
