#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance("127.0.0.1", 9999);

    cout<<atm.getAdvert()<<endl;
    if(atm.logIn("6771909456273272", 7709))
    {
        cout<<"Logged in successfull"<<endl;
 //       cout<<"Balance: "<<atm.getBalance()<<endl;
        const string anotherCard = "6771685347990238";
        const unsigned sum = 100;
        cout<<"Sending of $"<<sum<<" to "<<anotherCard<<(atm.sendMoneyTo(sum, anotherCard)? " was successfull" : " failed")<<endl;
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
