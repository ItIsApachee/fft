#include <apachee/fft/internal/reverse_bits.h>

#include <vector>
#include <cassert>
#include <stdint.h>

namespace apachee::fft::internal {




const std::vector<int64_t>& reverse_bits_batch(int bits) {
    if (reverse_bits_batch_cache.size() <= bits)
        reverse_bits_batch_cache.resize(bits + 1);
    
    assert(bits <= 60);
    assert(bits > 0);
    
    int sequence_size = int64_t{1} << bits;
    reverse_bits_batch_cache[bits].assign(sequence_size, 0);
    for (int64_t i = 0, k = 1, f = (int64_t{1} << (bits - 1)); i < bits; i++, k *= 2, f /= 2)
        for (int64_t j = int64_t{1} << i; j < sequence_size; j += k)
            reverse_bits_batch_cache[bits][j] |= f;
    for (int64_t i = 1; i < sequence_size; i++)
        reverse_bits_batch_cache[bits][i] ^= reverse_bits_batch_cache[bits][i - 1];

    return reverse_bits_batch_cache[bits];
}



}  // namespace apachee::fft::internal
