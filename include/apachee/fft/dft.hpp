#pragma once

#include <complex>
#include <cmath>
#include <vector>   
#include <numbers>
#include <stdexcept>
#include <stdint.h>

#include <apachee/fft/chirp_z.hpp>

namespace apachee::fft {



enum struct DftKind {
    // divide all coefficients by sqrt(N) for both DFT, and IDFT
    kDivideSqrtN,

    // divide all coefficient by N only for DFT
    kDivideN,

    // divide all coefficient by N only for IDFT
    kDivideNInverse,
};

template<typename RandomIt>
std::vector<std::complex<std::double_t>> dft(RandomIt first, RandomIt last, DftKind kind = DftKind::kDivideN);

template<typename RandomIt>
std::vector<std::complex<std::double_t>> idft(RandomIt first, RandomIt last, DftKind kind = DftKind::kDivideN);

template<typename RandomIt>
std::vector<std::complex<std::double_t>> dft(RandomIt first, RandomIt last, bool inverse, DftKind kind = DftKind::kDivideN);



template<typename RandomIt>
std::vector<std::complex<std::double_t>> dft(RandomIt first, RandomIt last, DftKind kind) {
    return dft(first, last, false, kind);
}

template<typename RandomIt>
std::vector<std::complex<std::double_t>> idft(RandomIt first, RandomIt last, DftKind kind) {
    return dft(first, last, true, kind);
}

template<typename RandomIt>
std::vector<std::complex<std::double_t>> dft(RandomIt first, RandomIt last, bool inverse, DftKind kind) {
    int64_t sequence_size = last - first;

    std::double_t angle = - 2 * std::numbers::pi_v<std::double_t> / static_cast<std::double_t>(sequence_size);
    std::double_t angle_multiplier = inverse ? -1 : 1;
    angle *= angle_multiplier;

    std::complex<std::double_t> C = std::exp(std::complex<std::double_t>{0, angle});
    auto result = chirp_z_transform(first, last, C);

    std::double_t c = 1;
    switch (kind) {
        case DftKind::kDivideN:
            if (inverse)
                break;
            c = sequence_size;
        case DftKind::kDivideNInverse:
            if (!inverse)
                break;
            c = sequence_size;
        case DftKind::kDivideSqrtN:
            c = std::sqrt(static_cast<std::double_t>(sequence_size));
        default:
            throw std::domain_error("unknown kind parameter");
    }

    for (auto& v : result) {
        v /= c;
    }

    return result;
}



} // namespace apachee::fft
