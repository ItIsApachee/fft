#pragma once

#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdint.h>

#include <apachee/fft/convolution.h>

namespace apachee::fft {



// Calculate polynomial in points C^0, C^1, C^2, C^3, ..., C^(m - 1),
// where n is the size of the given sequence
template<typename RandomIt>
std::vector<std::complex<std::double_t>> chirp_z_transform(RandomIt first, RandomIt last, std::complex<std::double_t> C, int64_t degree = -1) {
    int64_t sequence_size = last - first;
    if (degree == -1) {
        degree = sequence_size;
    }
    if (sequence_size == 0) {
        return std::vector<std::complex<std::double_t>>(degree, 0);
    }

    auto cn2 = [](int64_t n) {
        return n * (n - 1) / 2;
    };

    std::vector<std::complex<std::double_t>> c(sequence_size);
    for (int64_t i = 0; i < sequence_size; i++) {
        c[i] = *(first + i) * std::pow(C, -cn2(i));
    }
    std::reverse(c.begin(), c.end());

    std::vector<std::complex<std::double_t>> d(sequence_size + degree);
    for (int64_t i = 0; i < d.size(); i++) {
        d[i] = std::pow(C, cn2(i));
    }

    auto convolution_result = complex_convolution(c, d);
    convolution_result.resize(sequence_size + degree, 0);

    std::vector<std::complex<std::double_t>> result(degree);
    for (int64_t i = 0; i < degree; i++) {
        result[i] = convolution_result[sequence_size - 1 + i] / std::pow(C, cn2(i));
    }

    return result;
}



} // namespace apachee::fft
