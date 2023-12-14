#pragma once

#include <complex>
#include <cmath>
#include <vector>   
#include <numbers>
#include <stdint.h>

#include <apachee/fft/chirp_z.hpp>

namespace apachee::fft {



template<typename RandomIt>
std::vector<std::complex<std::double_t>> discrete_fourier_transform(RandomIt first, RandomIt last) {
    int64_t sequence_size = last - first;
    std::double_t angle = - 2 * std::numbers::pi_v<std::double_t> / static_cast<std::double_t>(sequence_size);
    std::complex<std::double_t> C = std::exp(std::complex<std::double_t>{0, angle});
    return chirp_z_transform(first, last, C);
}



} // namespace apachee::fft
