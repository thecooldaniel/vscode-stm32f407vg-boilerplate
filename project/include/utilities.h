#ifndef UTILITIES
#define UTILITIES

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void uint64_to_str(char *str, uint64_t input);
void init_str(char *str);

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

#endif