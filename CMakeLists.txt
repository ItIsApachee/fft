cmake_minimum_required(VERSION 3.25)

project(apachee_fft)

add_library(apachee_fft STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/reverse_bits.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/convolution.cc)
target_include_directories(apachee_fft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set_property(TARGET apachee_fft PROPERTY CXX_STANDARD 20)