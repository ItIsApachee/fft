cmake_minimum_required(VERSION 3.25)

project(apachee_fft)

add_library(apachee_fft INTERFACE)
target_include_directories(apachee_fft INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)