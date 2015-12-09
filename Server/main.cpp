#define NDEBUG

#include "Bank.h"

int main()
{
    Bank::getInstance("db4free.net", "w0rm", "w0rmer", "qwerty123", "192.168.0.116", 9999);
    return 0;
}
