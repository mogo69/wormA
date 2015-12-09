#ifndef _ATM_H_
#define _ATM_H_

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <string>
#include <array>
#include <vector>
using namespace std;

#include "../Requests/Request.h"
#include "../Responses/Response.h"

class ATM
{
public:
    class InnerCash;
    ~ATM();
    const bool isBlocked(const string& cardNumber);
    const bool setBlocked(const string& cardNumber);
    const bool logIn(const string& cardNumber, const unsigned PIN);
    const bool logOut();
    const bool changePIN(const unsigned PIN);
    const string getAdvert();
    const double getBalance();
    const bool canWithdraw(const unsigned sum);
    const bool withdraw(const unsigned sum, const bool useCreditMoney = false);
    const string getDataAbout(const string& cardNumber);
    const bool sendMoneyTo(const unsigned sum, const string& cardNumber);

    static ATM& getInstance(const string& bankHost, const unsigned bankPort);
private:
    string _bankHost;
    unsigned _bankPort;
    string _sessionKey;
    InnerCash * _innerCash;

    void processRequest(const boost::shared_ptr<Request>&, Response&);

    ATM(const string& bankHost, const unsigned bankPort);
    ATM(const ATM&);
    ATM& operator=(const ATM&);
};

class ATM::InnerCash
{
public:
    struct Pocket;
    InnerCash(const array<size_t,5> values   = { 200, 100, 50, 20, 10 },
              const array<size_t,5> ammounts = { 100, 100, 100, 100, 100 });
    ~InnerCash();
    bool canWithdraw(const size_t);
    bool withdraw(const size_t);
private:
    const size_t _numOfPockets;
    Pocket* _pockets;

    array<size_t,5> _cachedCombination {{0, 0, 0, 0, 0}};

    vector<array<size_t,5>> findSolutions(const size_t sum, size_t position = 0, array<size_t,5> combination = {0, 0, 0, 0, 0});
    size_t calculate(const array<size_t,5> &combination);
    array<size_t,5> chooseBestCombination(const vector<array<size_t,5>> &solutions);
    size_t sum(const array<size_t,5> &combination);
};

struct ATM::InnerCash::Pocket
{
    size_t _value;
    size_t _ammount;
};

#endif // ATM_H_
