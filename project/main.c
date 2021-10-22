#include "include/hal.h"
#include "include/randombytes.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #include <fcntl.h>
// #include <errno.h>
// #include <unistd.h>

#include "include/x25519/x25519-cortex-m4.h"

static int rand_fd = -1;

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


// static void init_rand(void) {
// 	rand_fd = open("/dev/urandom", O_RDONLY);
// 	if (rand_fd < 0) {
// 		perror("opening /dev/urandom");
// 		exit(1);
// 	}
// }

// static void randombytes(unsigned char* buf, int len) {
// 	if (rand_fd == -1) {
// 		fprintf(stderr, "rand_fd not initialized\n");
// 		exit(1);
// 	}

// 	int nread = 0;
// 	while (len) {
// 		int nbytes = read(rand_fd, buf + nread, len);
// 		if (nbytes < 0) {
// 			if (errno == EINTR) {
// 				continue;
// 			}
// 			perror("get_random_bytes");
// 			exit(1);
// 		}
// 		if (nbytes == 0) {
// 			fprintf(stderr, "rand_fd closed\n");
// 			exit(1);
// 		}
// 		nread += nbytes;
// 		len -= nbytes;
// 	}
// }

int main(void) {

    hal_setup(CLOCK_BENCHMARK);

	unsigned char secret_key_alice[32], secret_key_bob[32];
	unsigned char public_key_alice[32], public_key_bob[32];
	unsigned char shared_secret_alice[32], shared_secret_bob[32];

    uint64_t t1, t2, t_nofpu, t_withfpu;

	// init_rand();

	// Alice computes
	randombytes(secret_key_alice, 32);
    randombytes(secret_key_bob, 32);

    t1 = hal_get_time();

	// X25519_calc_public_key(public_key_alice, secret_key_alice);

	// // Bob computes

	// X25519_calc_public_key(public_key_bob, secret_key_bob);

	// // The public keys are now exchanged over some protocol

	// // Alice computes
	// X25519_calc_shared_secret(shared_secret_alice, secret_key_alice, public_key_bob);

	// // Bob computes
	// X25519_calc_shared_secret(shared_secret_bob, secret_key_bob, public_key_alice);

    curve25519_scalarmult(shared_secret_alice, secret_key_alice, secret_key_bob);

    t2 = hal_get_time();
    t_nofpu = t2 - t1;

	t1 = hal_get_time();
	// 476374
	curve25519_scalarmult_fpu(shared_secret_bob, secret_key_alice, secret_key_bob);
	t2 = hal_get_time();
	t_withfpu = t2 - t1;

    // Output results
    char str[21] = {'\0'};
    init_str(str);
    hal_send_str("\n##############################\n");
    uint64_to_str(str, t_nofpu);
    hal_send_str(str);
	hal_send_str("\n##############################\n");
	uint64_to_str(str, t_withfpu);
	hal_send_str("\n##############################\n");
	hal_send_str(str);
	hal_send_str("\n##############################\n");
	uint64_t num_correct = 0;
	for(int i = 0; i < 32; i++) {
		if(shared_secret_alice[i] == shared_secret_bob[i]) {
			num_correct++;
			// hal_send_str("yes");
		}
	}
	hal_send_str("Number of matches:\n");
	uint64_to_str(str, num_correct);
	hal_send_str(str);

	// if (memcmp(shared_secret_alice, shared_secret_bob, 32) == 0) {
	// 	puts("SUCCESS: Both Bob and Alice computed the same shared secret");
	// } else {
	// 	puts("FAILED: Bob and Alice did not compute the same shared secret");
	// 	exit(1);
	// }

	return 0;
}
