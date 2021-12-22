#include <stdio.h>
#include <stdint.h>
#include "include/hal.h"

extern uint32_t SignedMod(int32_t number, uint32_t divisor);
extern uint32_t UnsignedMod(uint32_t number, uint32_t divisor);

int main(void)
{
    hal_setup(CLOCK_BENCHMARK);

    uint32_t m = SignedMod(-10, 3);
    uint32_t m2 = UnsignedMod(538, 7);

    // You must use the launch target OpenOCD External/Semihosting for the below to work
    printf("Hello from semihosting!\n");

    while(1);

    return 0;
}
