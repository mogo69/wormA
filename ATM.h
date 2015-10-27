#ifndef _ATM_H_
#define _ATM_H_

#include <string>
using namespace std;

class ATM
{
public:
    class InnerCash;

    bool isBlocked();
    bool logIn(size_t cardN, size_t PIN);
    bool hasAdd();
    string getAdd();
    int getBalance();
    bool takeMoney(bool useCreditMoney);
    bool getDataAbout(size_t cardN);
    bool sendMoneyTo(size_t cardN);
    bool changePIN();
    static ATM& getInstance()
    {
        static ATM instance;
        return instance;
    }
private:
    ATM(){};
    ATM(const ATM& copy);
    ATM& operator=(const ATM&);

};

#include "InnerCash.h"

#endif // ATM_H_
