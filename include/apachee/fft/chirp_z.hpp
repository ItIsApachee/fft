#include <complex>
#include <cmath>
#include <vector>

namespace apachee::fft {



// Calculate polynomial in points C^0, C^1, C^2, C^3, ..., C^(n - 1),
// where n is the size of the given sequence
template<typename RandomIt>
std::vector<std::complex<std::double_t>> chirp_z_transform(RandomIt first, RandomIt last, std::complex<std::double_t> C);



} // namespace apachee::fft
