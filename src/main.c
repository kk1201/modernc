#include <stdio.h>
#include <math.h>

double merge_sort(double array[static 1], size_t size);

int main(int argc, char *argv[argc])
{
	// printf("Hello world");
	double array[] = { 3, 1, 6, 9 };
	merge_sort(array, 4);

	printf("Final product:\n");
	for (size_t i = 0; i < 4; ++i) {
		printf("[%zu]=%.0f", i, array[i]);
	}
}

double merge_sort(double array[static 1], size_t size)
{
	size_t new_size = ceil((float)size / 2);
	double arr1[new_size];
	double arr2[new_size];

	if (size != 2) {
		for (size_t i = 0; i < new_size; ++i) {
			arr1[i] = array[i];
			arr2[i] = array[i + (new_size)];
			printf("arr1[%zu]=%.0f arr2[%zu]=%.0f\n", i, arr1[i], i,
			       arr2[i]);
		}

		merge_sort(arr1, size / 2);
		merge_sort(arr2, size / 2);
	}

	if (array[0] < array[1]) {
		double temp = array[0];
		array[0] = array[1];
		array[1] = temp;
	}
	printf("[0]=%.0f [1]=%.0f\n", array[0], array[1]);

	return array[0];
}
