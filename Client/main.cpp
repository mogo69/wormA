#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance();
    if(atm.logIn("6709064673593456632", 6680))
    {
        cout<<"Logged in successfull"<<endl;
    }
    else
    {
        cout<<"Not looged in"<<endl;
    }
    return 0;
}
