#include <modbus/modbus.h>
#include <cstdint>
#include "loop.h"
int main(int argc, char** argv)
{
    while(1)
    {
        uint8_t a=1;
        loop();
    }
}