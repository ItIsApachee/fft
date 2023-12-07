#include <complex>
#include <cmath>
#include <bit>
#include <cassert>
#include <stdint.h>

#include <apachee/fft/internal/reverse_bits.h>

#pragma once

namespace apachee::fft::internal {

namespace constants {

std::double_t PI = std::acos(-1);

}  // namespace constants

template<typename RandomIt>
void fft(RandomIt first, RandomIt last, bool inverse = false) {
    int64_t sequence_size = last - first;
    if (sequence_size == 0)
        return;

    int sequence_size_log2 = std::bit_width(static_cast<std::uint64_t>(sequence_size)) - 1;
    assert((int64_t{1} << sequence_size_log2) == sequence_size);

    {
        std::vector<int64_t> result = reverse_bits_batch(sequence_size_log2);
        for (int i = 0; i < sequence_size; i++) {
            auto i_rev = result[i];
            if (i < i_rev)
                swap(*(first + i), *(first + i_rev));
        }
    }

    for (int block_size = 2; block_size <= sequence_size; block_size *= 2) {
        int half_block_size = block_size / 2;

        std::double_t power = 2 * (inverse ? -1 : 1) * constants::PI / block_size;
        std::complex<std::double_t> w0 = exp(std::complex<std::double_t>{0.0L, power});
        for (int i = 0; i < sequence_size; i += block_size) {
            std::complex<std::double_t> w = 1;
            for (int j = 0; j < half_block_size; j++, w *= w0) {
                std::complex<std::double_t> x = *(first + i + j);
                std::complex<std::double_t> y = *(first + i + j + half_block_size);
                y *= w;

                *(first + i + j) = x + y;
                *(first + i + j + half_block_size) = x - y;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < sequence_size; i++)
            *(first + i) /= static_cast<std::double_t>(sequence_size);
    }
}

}  // namespace apachee::fft::internal
