#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance();
    if(atm.logIn("12341234123", 1234))
    {
        cout<<"Logged in successfull"<<endl;
    }
    return 0;
}
