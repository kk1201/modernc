cmake_minimum_required(VERSION 3.10)
project(ModernC)

add_executable(ModernC src/main.c)
target_link_libraries(ModernC m)
