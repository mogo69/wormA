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
    bool isBlocked();
    bool logIn(const string cardN, const unsigned PIN);
    bool logOut();
    bool changePIN(const size_t PIN);
    string getAdvert();
    double getBalance();
    bool canWithdraw(size_t sum);
    bool withdraw(const size_t amount, const bool useCreditMoney = false);
    string getDataAbout(const string cardN);
    bool sendMoneyTo(const string cardN);

    static ATM& getInstance(const string&, const unsigned);
private:
    string _bankHost;
    unsigned _bankPort;
    string _sessionKey;
    InnerCash * _innerCash;

    void processRequest(const boost::shared_ptr<Request>&, Response&);

    ATM(const string&, const unsigned);
    ATM(const ATM&);
    ATM& operator=(const ATM&);
};

class ATM::InnerCash
{
public:
    struct Pocket;
    InnerCash(const array<size_t,5> values   = { 10, 20, 50, 100, 200 },
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
