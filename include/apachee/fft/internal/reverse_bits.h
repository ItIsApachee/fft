#include <vector>
#include <cassert>
#include <stdint.h>

#pragma once

namespace apachee::fft::internal {



std::vector<std::vector<int64_t>> reverse_bits_batch_cache;
const std::vector<int64_t>& reverse_bits_batch(int bits);



}  // namespace apachee::fft::internal
