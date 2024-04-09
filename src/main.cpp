#include <cmath>
#include <iostream>
#include <modbus/modbus.h>
#include <cstdint>
#include "loop.h"

int main(int argc, char **argv)
{

    uint8_t a=1;
    modbus_t * ctx;
    ctx = modbus_new_tcp("127.0.0.1", 1502);
    while (1)
    {
        
    }
}