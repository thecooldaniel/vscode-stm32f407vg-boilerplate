#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "include/hal.h"
#include "include/utilities.h"
#include "include/randombytes.h"


int main(void) {

	#ifdef SEMIHOSTING
		initialise_monitor_handles();
	#endif
    hal_setup(CLOCK_BENCHMARK);

	/* START CODE HERE */

	/* Test ASM */
	uint32_t m = SignedMod(-10, 3);
    uint32_t m2 = UnsignedMod(538, 7);

	/* Test randombytes */
	unsigned char rb[32];
	randombytes(rb, 32);

	/* Test file IO */
	FILE *f = fopen("semihosting_test.txt", "w+");
	fprintf(f, "Test if fileio semihosting works");
	fclose(f);

	/* Test terminal semihosting */
	printf("Test if semihosting works. Output must end with a new line\n");

	/** 
	 * Test USART out
	 * The below probably wont work with '--specs=rdimon.specs -lc -lrdimon' included in the C flags
	 */
	/*
	char str[21] = {'\0'};
	uint64_t n_out = 0x1234;
	init_str(str);
	hal_send_str("\n##############################\n");
	uint64_to_str(str, n_out);
	hal_send_str(str);
	hal_send_str("\n##############################\n");
	*/

    while(1);

	return 0;
}
