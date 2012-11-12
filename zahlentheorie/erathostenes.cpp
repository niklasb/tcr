#include <cstring>

unsigned *sieve(unsigned *next, unsigned high) {
    unsigned char isprime[(high >> 4) + 1];
    unsigned i, j;
 
    memset(isprime, 0, (high >> 4) + 1);
    if (2 <= high) {
	*next++ = 2;
    }
 
    for (i = 3; i <= high; i += 2) {
	if ((isprime[i >> 4] & (1 << ((i >> 1) & 7))) == 0) {
	    *next++ = j = i;
	    while ((j += i << 1) <= high) {
		isprime[j >> 4] |= 1 << ((j >> 1) & 7);
	    }
	}
    }
 
    return next;
}
