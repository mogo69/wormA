#ifndef _BANK_H_
#define _BANK_H_

#include <string>
using namespace std;

class Bank
{
private:
    string _dbHost;
    string _dbName;
    string _dbUser;
    string _dbPass;
    string _host;
    size_t _port;

    Bank(const string& dbHost,
        const string& dbName,
        const string& dbUser,
        const string& dbPass,
        const string& host,
        size_t port );

    bool takeMoney(size_t cardNumber, size_t amount, bool useCreditMoney = false);
    string getData(size_t cardNumber);
    bool sendMoney(size_t from, size_t to);
    double getBalance(size_t cardNumber);
    string getAdvert();
    bool changePIN(size_t cardNumber, size_t newPIN);
    bool checkAuth(size_t cardNumber, size_t PIN);
    bool isBlocked(size_t cardNumber);

    Bank(const Bank&);
    Bank& operator=(const Bank&);

public:
    ~Bank();
    static Bank& getInstance(const string& dbHost,
        const string& dbName,
        const string& dbUser,
        const string& dbPass,
        const string& host,
        size_t port);
};

#endif // _BANK_H_
