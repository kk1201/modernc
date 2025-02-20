#include <stddef.h>
#include <stdio.h>

void merge_sort_example(void)
{
	double array[] = { 3, 1, 6, 9, 11, 10, 20 };
	size_t size = sizeof(array) / sizeof(array[0]);

	printf("Final product:\n");
	for (size_t i = 0; i < size; ++i) {
		printf("[%zu]=%.0f", i, array[i]);
	}
	puts("\n");
}
