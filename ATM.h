#ifndef _ATM_H_
#define _ATM_H_

#include <string>
using namespace std;

class ATM
{
public:
    class InnerCash;
    bool isBlocked();
    bool logIn(const string cardN, const size_t PIN);
    bool logOut();
    bool hasAdvert();
    string getAdvert();
    double getBalance();
    bool takeMoney(const double amount, bool useCreditMoney = false);
    bool getDataAbout(const string cardN);
    bool sendMoneyTo(const string cardN);
    bool changePIN(const size_t PIN);
    static ATM& getInstance()
    {
        static ATM instance;
        return instance;
    }
private:
    string _cardN;
    InnerCash * _innerCash;

    ATM(){};
    ATM(const ATM&);
    ATM& operator=(const ATM&);

};

class ATM::InnerCash
{
    InnerCash(){};
    ~InnerCash(){};
};

//#include "InnerCash.h"

#endif // ATM_H_
