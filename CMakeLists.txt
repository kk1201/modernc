cmake_minimum_required(VERSION 3.10)
project(ModernC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(ModernC 
	src/main.c
	src/k_file_io.c
	src/merge_sort.c
)
target_include_directories(ModernC PRIVATE include/)

set(CMAKE_C_FLAGS_DEBUG "-g -std=c99 -Wpedantic -pedantic-errors -Werror -Wall -Wextra -Waggregate-return -Wbad-function-cast -Wcast-align -Wcast-qual -Wfloat-equal -Wformat=2 -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wredundant-decls -Wsequence-point -Wshadow -Wstrict-prototypes -Wswitch -Wundef -Wunreachable-code -Wunused-but-set-parameter -Wwrite-strings -fsanitize=address")
# add_compile_options(-fsanitize=address)
target_link_libraries(ModernC m)
