cmake_minimum_required(VERSION 2.8.3)
project(vfork_utils)

add_library(vfork_utils SHARED popen.c system.c)

install(TARGETS vfork_utils DESTINATION lib)
