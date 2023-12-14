#include <vector>
#include <cmath>
#include <complex>

namespace apachee::fft {



std::vector<std::double_t>
convolution(
        const std::vector<std::double_t>& a, const std::vector<std::double_t>& b,
        std::double_t eps = 1E-12);

std::vector<std::complex<std::double_t>>
complex_convolution(
        const std::vector<std::complex<std::double_t>>& a, const std::vector<std::complex<std::double_t>>& b,
        std::double_t eps = 1E-12);



}  // namespace apachee::fft