#include "k_fileio.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k_file_arg_o(int argc, char *argv[argc]);
int k_file_input_o(int line_nums);
int k_print_file(const char *path, int line_nums);
int k_text_output(int argc, char *argv[argc]);
char *k_getinput(void);
int final_char(char buf[]);

int k_file_arg_o(int argc, char *argv[argc])
{
	argc = argc;
	argv = argv;
	return 0;
}

int k_file_input_o(int line_nums)
{
	line_nums = line_nums;
	return 0;
}

int k_print_file(const char *path, int line_nums)
{
	int ret = EXIT_FAILURE;
	FILE *istream = fopen(path, "r");
	char buffer[buf_max] = { 0 };
	int line_num = 0;

	if (!istream) {
		fprintf(stderr, "Couldn't open %s\n", path);
		perror(0);
		errno = 0;
		ret = EXIT_FAILURE;
	}
	printf("---File [%s]---\n", path);
	while (fgets(buffer, buf_max, istream)) {
		if (line_nums) {
			fprintf(stdout, "%3d| ", line_num);
		}
		fputs(buffer, stdout);
		if (final_char(buffer) != '\n') {
			fputc('\n', stdout);
		}

		line_num++;
	}

	return ret;
}

int k_text_output(int argc, char *argv[argc])
{
	int ret = EXIT_FAILURE;
	int start = 1;
	int line_nums = 0;

	if (strcmp(argv[1], "-n") == 0) {
		line_nums = 1;
		start++;
	}

	if (argc == 1) {
		// char *input = malloc(sizeof(char) * buf_max);
		ret = k_file_input_o(line_nums);
	} else {
		ret = k_file_arg_o(argc, argv);
	}

	return ret;
}

int final_char(char buf[])
{
	int ret = 0;

	if (!buf) {
		return -1;
	}

	ret = *buf;
	while (*++buf != 0) {
		ret = *buf;
	}
	// printf(" apparently final char is %d! ", ret);

	return ret;
}
