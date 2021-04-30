#include "include/stm32wrapper.h"

#include <stdio.h>

extern void playground();
extern void swap(uint32_t *a, uint32_t *b);
extern void foo();
extern int64_t Mult64x64(int64_t A, int64_t B);
extern int32_t ComputeDiscriminant(int32_t a, int32_t b, int32_t c);
extern uint32_t SignedMod(int32_t number, uint32_t divisor);
extern uint32_t UnsignedMod(uint32_t number, uint32_t divisor);

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    // uint32_t *a;
    // uint32_t *b;

    // uint32_t aa = 2;
    // uint32_t bb = 4;
    // a = &aa;
    // b = &bb;
    // swap(a,b);

    // foo();
    int64_t A = 294967296;
    int64_t B = 294967296;
    int64_t C = Mult64x64(A,B);

    int32_t x = 4;
    int32_t y = 6;
    int32_t z = 8;

    int32_t zz = ComputeDiscriminant(x,y,z);

    x = 10;
    y = 20;
    z = 300;
    zz = ComputeDiscriminant(x,y,z);

    uint32_t m = SignedMod(-10, 3);
    uint32_t m2 = UnsignedMod(538, 7);

    z = 1;

    // char output[16];
    // sprintf(output, "output: %02X\n", a);

    // send_USART_str((unsigned char*)output);

    while(1);

    return 0;
}
