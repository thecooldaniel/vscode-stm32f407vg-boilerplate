#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "include/hal.h"
#include "include/utilities.h"


int main(void) {

    hal_setup(CLOCK_BENCHMARK);

	// Test ASM
	uint32_t m = SignedMod(-10, 3);
    uint32_t m2 = UnsignedMod(538, 7);

	// Test randbytes
	uint32_t rb[32];
	randombytes(rb, 32);

	// Test semihosting
	printf("Test if semihosting works. Output must end with a new line\n");

	// Test UART out
	char str[20];
	uint64_t n_out = 0xffffffffffffffff;
	init_str(str);
	uint64_to_str(str, n_out);
	hal_send_str(str);

    while(1);

	return 0;
}
