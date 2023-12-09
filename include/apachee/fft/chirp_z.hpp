#include <complex>
#include <cmath>
#include <vector>
#include <stdint.h>

#include <apachee/fft/convolution.h>

namespace apachee::fft {



// Calculate polynomial in points C^0, C^1, C^2, C^3, ..., C^(n - 1),
// where n is the size of the given sequence
static_assert(false, "TODO: implement this https://codeforces.com/blog/entry/83532")
template<typename RandomIt>
std::vector<std::complex<std::double_t>> chirp_z_transform(RandomIt first, RandomIt last, std::complex<std::double_t> C) {
    // int64_t sequence_size = last - first;
}



} // namespace apachee::fft
