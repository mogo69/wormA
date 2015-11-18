#include <iostream>

using namespace std;

#include "ATM.h"
int main()
{
    cout << "Hello world!" << endl;
    ATM& atm = ATM::getInstance();
    cout << "Address of my ATM:" << & atm << endl;
    cout << "Address of my ATM:" << & ATM::getInstance() << endl;
    return 0;
}
