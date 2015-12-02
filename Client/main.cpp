#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance();
 /*   cout << atm.canWithdraw(1000) << endl;
    while(atm.canWithdraw(1000))
    {
        atm.withdraw(1000);
    }
    while(atm.canWithdraw(70))
    {
        atm.withdraw(70);
    }
*/
    cout<<atm.getAdvert()<<endl;
    //if(atm.logIn("6771685347990238", 1783))
    if(atm.logIn("6771909456273272", 7709))
    {
        cout<<"Logged in successfull"<<endl;
        cout<<atm.getBalance()<<endl;
        atm.withdraw(10);
        cout<<atm.getDataAbout("6771172914064622")<<endl;
    }
    else
    {
        cout<<"Not looged in"<<endl;
    }
    /*if(atm.logIn("6771257034355469", 9056))
    {
        cout<<"Logged in successfull"<<endl;
    }
    else
    {
        cout<<"Not looged in"<<endl;
    }*/
    atm.logOut();
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
