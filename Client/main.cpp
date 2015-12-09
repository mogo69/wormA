#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance("192.168.0.116", 9999);
//    cout<<atm.getAdvert();
//    cout<<atm.isBlocked("0604384783441263")<<endl;
//    cout<<atm.isBlocked("0604229556198639")<<endl;
//    cout<<atm.block("0604229556198639")<<endl;
//    cout<<atm.isBlocked("0604229556198639")<<endl;
    if(atm.logIn("0604229556198639", 3489))
    {
        cout<<"Logged in successfull"<<endl;

//        const string anotherCard = "0604384783441263";
        const string anotherCard = "0604229556198639";
        const unsigned sum = -10000;
        cout<<"Sending of $"<<sum<<" to "<<anotherCard<<(atm.sendMoneyTo(sum, anotherCard)? " was successfull" : " failed")<<endl;

      /*  cout<<"Balance: "<<atm.getBalance()<<endl;
        cout<<"Balance: "<<atm.withdraw(9000, true)<<endl;
        cout<<"Balance: "<<atm.getBalance()<<endl;
 //       const string anotherCard = "6771685347990238";*/
 //       const unsigned sum = 100;
 //       cout<<"Sending of $"<<sum<<" to "<<anotherCard<<(atm.sendMoneyTo(sum, anotherCard)? " was successfull" : " failed")<<endl;

    }
    else
    {
        cout<<"Not logged in"<<endl;
    }
    if(atm.logOut())
    {
        cout<<"Successfully logged out"<<endl;
    }
    return 0;
}
