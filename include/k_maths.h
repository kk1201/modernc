#ifndef K_MATHS
#define K_MATHS

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int64_t rand_num(int64_t min, int64_t max)
{
	return ((rand() % (min - max)) + min);
}

// Copied from book
uint64_t gcd2(uint64_t a, uint64_t b)
{
	assert(a <= b);
	if (!a)
		return b;

	return gcd2((b % a), a);
}

// Copied from book
uint64_t gcd(uint64_t a, uint64_t b)
{
	assert(a);
	assert(b);
	if (a < b) {
		return gcd2(a, b);
	} else {
		return gcd2(b, a);
	}
}
#endif
