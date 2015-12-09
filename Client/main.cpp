#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance("192.168.0.108", 9999);
    cout<<atm.getAdvert()<<endl;
    if(atm.logIn("6771909456273272", 7709))
    {
        cout<<"Logged in successfull"<<endl;
        cout<<atm.getBalance()<<endl;

        atm.withdraw(10);
        cout<<atm.getBalance()<<endl;

    }
    else
    {
        cout<<"Not logged in"<<endl;
    }
    atm.logOut();
    return 0;
}
