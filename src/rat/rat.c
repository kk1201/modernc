#include <time.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "rat.h"
#include "k_error.h"

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

// Copied from book
k_error rat_get(rat *out, int64_t num, uint64_t denom)
{
	if (!out) {
		return K_FAIL;
	}
	out->sign = (num < 0);
	out->num = (num < 0) ? -num : num;
	out->denom = denom;

	return K_SUCCESS;
}

// Copied from book
k_error rat_normalise(rat *rp)
{
	if (!rp)
		return K_FAIL;
	uint64_t c = gcd(rp->num, rp->denom);
	rp->num /= c;
	rp->denom /= c;

	return K_SUCCESS;
}

k_error rat_get_normal(rat *out, rat const *in)
{
	if (!out || !in)
		return K_FAIL;
	rat_copy(out, in);
	rat_normalise(out);

	return K_SUCCESS;
}

k_error rat_get_extended(rat *rp, uint64_t f)
{
	if (!rp)
		return K_FAIL;
	rp->num *= f;
	rp->denom *= f;

	return K_SUCCESS;
}

k_error rat_copy(rat *out, rat const *in)
{
	out->sign = in->sign;
	out->num = in->num;
	out->denom = in->denom;

	return K_SUCCESS;
}

// Copied from book
k_error rat_sumup(rat *rp, rat y)
{
	rp = rp;
	y = y;
	return K_SUCCESS;
}

k_error rat_dotproduct(rat *rp, size_t n, rat const a[static 1],
		       rat const b[static 1])
{
	uint64_t num = 0;
	uint64_t denom = 0;
	for (size_t i = 0; i < n; ++i) {
		rat normal_ai;
		rat normal_bi;
		rat_get_normal(&normal_ai, &a[i]);
		rat_get_normal(&normal_bi, &b[i]);
		// TODO
	}

	rp->num = num;
	rp->denom = denom;
	rp->sign = a->sign;

	return K_SUCCESS;
}

void rat_print(rat *rp)
{
	char sign = (rp->sign) ? '-' : '+';
	printf("%c%zu/%zu\n", sign, rp->num, rp->denom);
}

void rat_print_normalised(rat *rp)
{
	rat temp = { 0 };
	rat_copy(&temp, rp);
	rat_normalise(&temp);
	rat_print(&temp);
}

void rat_print_array(rat arr[static 1], size_t size)
{
	for (size_t i = 0; i < size; ++i) {
		printf("[%zu] = ", i);
		rat_print(&arr[i]);
	}
}

int64_t rand_num(int64_t min, int64_t max)
{
	return ((rand() % (min - max)) + min);
}

void rat_print_example(void)
{
	rat r = { .sign = false, .num = 20, .denom = 5 };
	rat_print(&r);

	rat_get(&r, -30, 20);
	rat_print(&r);

	rat_print_normalised(&r);

	rat_normalise(&r);
	rat_print(&r);

	size_t arr_max = 3;
	rat arr_a[arr_max];
	rat arr_b[arr_max];
	srand(time(NULL));

	for (size_t i = 0; i < arr_max - 1; ++i) {
		rat tmp = { 0 };
		rat_get(&tmp, rand_num(-10, 20), rand_num(1, 20));
		rat_copy(&arr_a[i], &tmp);
	}

	srand(time(NULL) + 1);
	for (size_t i = 0; i < arr_max - 1; ++i) {
		rat tmp = { 0 };
		rat_get(&tmp, rand_num(-10, 20), rand_num(1, 20));
		rat_copy(&arr_b[i], &tmp);
	}

	printf("arr_a:\n");
	rat_print_array(arr_a, arr_max - 1);
	printf("arr_b:\n");
	rat_print_array(arr_b, arr_max - 1);

	rat_dotproduct(&r, arr_max, arr_a, arr_b);
	// rat_normalise(&r);
	// rat_print(&r);
}
