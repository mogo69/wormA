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

    static const string SQL_GET_ALL_ACCOUNTS;

    string _dbHost;
    string _dbName;
    string _dbUser;
    string _dbPass;
    string _host;
    size_t _port;

    Bank(const string& dbHost = "localhost",
        const string& dbName = "cpp",
        const string& dbUser = "cpp_user",
        const string& dbPass = "cppqwerty123",
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
    static Bank& getInstance();
    string process(const Transaction&);
};

#endif // _BANK_H_
