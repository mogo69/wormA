#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance();
    cout << atm.canWithdraw(1000) << endl;
    while(atm.canWithdraw(1000))
    {
        atm.withdraw(1000);
    }
    while(atm.canWithdraw(70))
    {
        atm.withdraw(70);
    }
    /*if(atm.logIn("6767959408184551137", 9253))
    //if(atm.logIn("6767207064848269564", 5406))
    {
        cout<<"Logged in successfull"<<endl;
    }
    else
    {
        cout<<"Not looged in"<<endl;
    }
/*    if(atm.logOut())
    //if(atm.logIn("6767207064848269564", 5406))
    {
        cout<<"Logged out successfull"<<endl;
    }
    else
    {
        cout<<"Not looged out"<<endl;
    }*/
    return 0;
}
