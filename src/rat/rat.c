#include <time.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include "rat.h"
#include "k_maths.h"

rat rat_get(int64_t num, uint64_t denom)
{
	rat ret = { .sign = (num < 0),
		    .num = (num < 0) ? -num : num,
		    .denom = denom };

	return ret;
}

rat rat_get_normal(rat x)
{
	uint64_t c = gcd(x.num, x.denom);
	x.num /= c;
	x.denom /= c;

	return x;
}

rat rat_get_extended(rat x, uint64_t f)
{
	x.num *= f;
	x.denom *= f;

	return x;
}

rat rat_get_prod(rat x, rat y)
{
	rat ret = { .sign = (x.sign != y.sign),
		    .num = x.num * y.num,
		    .denom = x.denom * y.denom };

	return rat_get_normal(ret);
}

rat rat_get_sum(rat x, rat y)
{
	if (x.num == 0)
		return y;
	else if (y.num == 0)
		return x;

	uint64_t c = gcd(x.denom, y.denom);
	uint64_t ax = y.denom / c;
	uint64_t bx = x.denom / c;

	x = rat_get_extended(x, ax);
	y = rat_get_extended(y, bx);
	assert(x.denom == y.denom);

	if (x.sign == y.sign) {
		x.num += y.num;
	} else if (x.num > y.num) {
		x.num -= y.num;
	} else {
		x.num = y.num - x.num;
		x.sign = !x.sign;
	}

	return rat_get_normal(x);
}

rat *rat_init(rat *rp, int64_t num, uint64_t denom)
{
	if (rp)
		*rp = rat_get(num, denom);

	return rp;
}

rat *rat_copy(rat *rp, rat y)
{
	if (rp)
		*rp = (rat){ .sign = y.sign, .num = y.num, .denom = y.denom };

	return rp;
}

rat *rat_normalise(rat *rp)
{
	if (rp)
		*rp = rat_get_normal(*rp);

	return rp;
}

rat *rat_extend(rat *rp, uint64_t f)
{
	if (rp)
		*rp = rat_get_extended(*rp, f);

	return rp;
}

rat *rat_sumup(rat *rp, rat y)
{
	uint64_t c = gcd(rp->denom, y.denom);
	uint64_t ax = y.denom / c;
	uint64_t bx = rp->denom / c;

	rat_extend(rp, ax);
	y = rat_get_extended(y, bx);
	assert(rp->denom == y.denom);

	if (rp->sign == y.sign) {
		rp->num += y.num;
	} else if (rp->num > y.num) {
		rp->num -= y.num;
	} else {
		rp->num = y.num - rp->num;
	}

	return rat_normalise(rp);
}

rat *rma(rat *rp, rat x, rat y)
{
	return rat_sumup(rp, rat_get_prod(x, y));
}

void rat_print(rat *rp)
{
	if (!rp)
		return;

	char sign = (rp->sign) ? '-' : '+';
	printf("%c%zu/%zu\n", sign, rp->num, rp->denom);
}

void rat_print_normalised(rat *rp)
{
	if (!rp)
		return;

	rat_print(rat_normalise(rp));
}

void rat_print_array(rat arr[static 1], size_t size)
{
	assert(arr);

	for (size_t i = 0; i < size; ++i) {
		printf("[%zu] = ", i);
		rat_print(&arr[i]);
	}
}

void rat_print_remainder(rat *rp)
{
	assert(rp);

	size_t whole = rp->num / rp->denom;
	size_t remainder = rp->num % rp->denom;
	char sign = (rp->sign) ? '-' : '+';

	printf("%c%zu %zu/%zu\n", sign, whole, remainder, rp->denom);
}

rat rat_get_sum_array(size_t n, rat const A[n])
{
	assert(A && n > 0);
	if (n == 1)
		return A[0];

	rat ret = { 0 };
	for (size_t i = 0; i < n; ++i) {
		ret = rat_get_sum(ret, A[i]);
	}

	return ret;
}

rat *rat_dotproduct(rat *rp, size_t n, rat const A[n], rat const B[n])
{
	assert(rp);
	if (n <= 0 || !A || !B)
		return 0;

	rat temp[n];
	for (size_t i = 0; i < n; ++i) {
		rat_init(&temp[i], 0, 0);
	}

	for (size_t i = 0; i < n; ++i) {
		temp[i] = rat_get_prod(A[i], B[i]);
	}

	*rp = rat_get_sum_array(n, temp);
	rat_normalise(rp);

	return rp;
}

void rat_print_example(void)
{
	rat r = { .sign = false, .num = 20, .denom = 5 };
	rat_print(&r);

	rat_init(&r, -30, 20);
	rat_print(&r);

	rat_print_normalised(&r);

	rat_normalise(&r);
	rat_print(&r);

	size_t arr_max = 3;
	rat arr_a[arr_max];
	rat arr_b[arr_max];
	srand(time(NULL));

	for (size_t i = 0; i < arr_max; ++i) {
		rat tmp = rat_get(rand_num(1, 20), rand_num(1, 20));
		rat_copy(&arr_a[i], tmp);
	}

	srand(time(NULL) + 1);
	for (size_t i = 0; i < arr_max; ++i) {
		rat tmp = rat_get(rand_num(1, 20), rand_num(1, 20));
		rat_copy(&arr_b[i], tmp);
	}

	printf("arr_a:\n");
	rat_print_array(arr_a, arr_max);
	printf("arr_b:\n");
	rat_print_array(arr_b, arr_max);

	// rat_print(rat_sumup(&arr_a[0], arr_b[0]));

	rat_dotproduct(&r, arr_max, arr_a, arr_b);
	rat_print_normalised(&r);
	rat_print_remainder(&r);
}
