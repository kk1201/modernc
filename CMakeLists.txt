cmake_minimum_required(VERSION 3.10)
project(ModernC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ModernC 
	src/main.c
	src/fileio/k_file_io.c
	src/mergesort/merge_sort.c
	src/rat/rat.c
)
target_include_directories(ModernC PRIVATE include/)

set(CMAKE_C_FLAGS_DEBUG "-g -std=c99 -Wpedantic -pedantic-errors -Werror -Wall -Wextra -Wbad-function-cast -Wcast-align -Wcast-qual -Wfloat-equal -Wformat=2 -Wlogical-op -Wmissing-include-dirs -Wnested-externs -Wpointer-arith -Wredundant-decls -Wsequence-point -Wshadow -Wstrict-prototypes -Wswitch -Wundef -Wunreachable-code -Wunused-but-set-parameter -Wwrite-strings -fsanitize=address")
target_link_libraries(ModernC m)
