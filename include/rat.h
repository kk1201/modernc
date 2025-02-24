#ifndef RAT_H
#define RAT_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include "k_error.h"

typedef struct rat {
	bool sign;
	size_t num;
	size_t denom;
} rat;

void rat_print(struct rat *rp);

void rat_print_example(void);

rat *rat_copy(rat *out, rat y);
#endif /* ifndef RAT_H */
