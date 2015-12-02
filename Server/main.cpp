#define NDEBUG

#include "Bank.h"

int main()
{
    Bank::getInstance("db4free.net", "w0rm", "w0rmer", "qwerty123", "127.0.0.1", 9999);
    return 0;
}
