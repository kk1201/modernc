#include <stdio.h>
#include "merge_sort.h"
#include "k_fileio.h"

void modulo_hour_example(void);

int main(int argc, char *argv[argc])
{
	argv = argv;
	// if (text_output(argc, argv) == EXIT_FAILURE) {
	// 	return EXIT_FAILURE;
	// }
	// modulo_hour_example();
	// k_fileio_example();
	merge_sort_example();
}

void modulo_hour_example(void)
{
	int length, hour, minute_0 = 0;
	int res_hour, res_minute0 = 0;
	scanf("%d %d:%d", &length, &hour, &minute_0);

	res_hour = (hour + length) % 24;
	res_minute0 = minute_0 % 60;
	printf("%d hours after %d:%02d is %d:%02d\n", length, hour, minute_0,
	       res_hour, res_minute0);
}

void print_array(double array[static 1], size_t size)
{
	printf("-- Array of size %zu --\n", size);
	for (size_t i = 0; i < size; ++i) {
		printf("[%zu]=%.0f\n", i, array[i]);
	}
	printf("-- End of array of size %zu --\n", size);
}
