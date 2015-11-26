#include <iostream>
using namespace std;

#include "ATM.h"

int main()
{
    ATM& atm = ATM::getInstance();
    if(atm.logIn("6767959408184551137", 9253))
    //if(atm.logIn("6767207064848269564", 5406))
    {
        cout<<"Logged in successfull"<<endl;
    }
    else
    {
        cout<<"Not looged in"<<endl;
    }
    return 0;
}
