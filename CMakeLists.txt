cmake_minimum_required(VERSION 2.8.3)
project(popen_vfork)

add_library(popen_vfork SHARED popen.c)

install(TARGETS popen_vfork DESTINATION lib)
