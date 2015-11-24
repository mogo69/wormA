/*
 * ATM.h
 * Author: Vitalii Moholivskyi
 *
 */

#ifndef _ATM_H_
#define _ATM_H_

#include <string>
using namespace std;

#include "../Connection/TCPStream.h"
#include "../Connection/TCPConnector.h"
class ATM
{
public:
    class InnerCash;
    ~ATM();
    bool isBlocked();
    bool logIn(const string cardN, const size_t PIN);
    bool logOut();
    bool changePIN(const size_t PIN);
    bool hasAdvert();
    string getAdvert();
    double getBalance();
    bool takeMoney(const double amount, bool useCreditMoney = false);
    bool getDataAbout(const string cardN);
    bool sendMoneyTo(const string cardN);

    static ATM& getInstance();
private:
    TCPConnector* _connector;
    TCPStream* _stream;
    string _sesionKey;
    InnerCash * _innerCash;

    ATM();
    ATM(const ATM&);
    ATM& operator=(const ATM&);

};

class ATM::InnerCash
{
public:
    struct Pocket;
    InnerCash();
    ~InnerCash();
    bool canWithdraw(const double);
    void withdraw(const double);
private:
    Pocket* _pockets;
};

struct ATM::InnerCash::Pocket
{
    size_t _quantity;
    size_t _value;
};

#endif // ATM_H_
