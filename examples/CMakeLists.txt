add_executable(apachee_fft_czt czt.cc)
target_link_libraries(apachee_fft_czt PRIVATE apachee_fft)
set_property(TARGET apachee_fft_czt PROPERTY CXX_STANDARD 20)

add_executable(apachee_fft_internal fft_internal.cc)
target_link_libraries(apachee_fft_internal PRIVATE apachee_fft)
set_property(TARGET apachee_fft_internal  PROPERTY CXX_STANDARD 20)

add_executable(apachee_fft_dft dft.cc)
target_link_libraries(apachee_fft_dft PRIVATE apachee_fft)
set_property(TARGET apachee_fft_dft PROPERTY CXX_STANDARD 20)

add_executable(apachee_fft_interpolate interpolate.cc)
target_link_libraries(apachee_fft_interpolate PRIVATE apachee_fft)
set_property(TARGET apachee_fft_interpolate PROPERTY CXX_STANDARD 20)