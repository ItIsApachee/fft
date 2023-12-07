#include <complex>
#include <cmath>
#include <bit>
#include <cassert>
#include <stdint.h>

#include <apachee/fft/internal/reverse_bits.h>

#pragma once

namespace apachee::fft::internal {

using base_float = std::double_t;

base_float PI = std::acos(-1);

template<typename RandomIt>
void fft(RandomIt first, RandomIt last, bool inverse = false) {
    int64_t sequence_size = last - first;
    if (sequence_size == 0)
        return;

    int sequence_size_log2 = std::bit_width(sequence_size) - 1;
    assert((int64_t{1} << sequence_size_log2) == n);

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

        base_float power = 2 * (inverse ? -1 : 1) * PI / block_size;
        std::complex<base_float> w0 = exp(std::complex<base_float>{0.0L, power});
        for (int i = 0; i < sequence_size; i += block_size) {
            std::complex<base_float> w = 1;
            for (int j = 0; j < half_block_size; j++, w *= w0) {
                std::complex<base_float> x = *(first + i + j);
                std::complex<base_float> y = *(first + i + j + half_block_size);
                y *= w;

                *(first + i + j) = x + y;
                *(first + i + j + half_block_size) = x - y;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < sequence_size; i++)
            *(first + i) /= static_cast<base_float>(sequence_size);
    }
}

}  // namespace apachee::fft::internal
