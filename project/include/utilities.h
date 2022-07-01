#ifndef UTILITIES
#define UTILITIES

#include <stdint.h>
#include <libopencm3/stm32/rng.h>

void uint64_to_str(char *str, uint64_t input);
void init_str(char *str);
void randombytes(unsigned char *x,unsigned long long xlen);

void uint64_to_str(char *str, uint64_t input) {
    // https://stackoverflow.com/questions/8257714/how-to-convert-an-int-to-string-in-c
    int slength = snprintf( NULL, 0, "%llu", (unsigned long long)input );
    // str = malloc( slength + 1 );
    snprintf(str, slength + 1, "%llu", (unsigned long long)input );
}

void init_str(char *str) {
    int i;
    for(i = 0; i < 20; i++)
        str[i] = ' ';
}

/*
This implementation taken from:
https://github.com/mupq/nttm4
*/
//TODO Maybe we do not want to use the hardware RNG for all randomness, but instead only read a seed and then expand that using fips202.
void randombytes(unsigned char *x,unsigned long long xlen)
{
    union
    {
        unsigned char aschar[4];
        uint32_t asint;
    } random;

    while (xlen > 4)
    {
        random.asint = rng_get_random_blocking();
        *x++ = random.aschar[0];
        *x++ = random.aschar[1];
        *x++ = random.aschar[2];
        *x++ = random.aschar[3];
        xlen -= 4;
    }
    if (xlen > 0)
    {
        for (random.asint = rng_get_random_blocking(); xlen > 0; --xlen)
        {
            *x++ = random.aschar[xlen - 1];
        }
    }
}


#endif