#include <vector>
#include <cmath>

namespace apachee::fft {



std::vector<std::double_t>
convolution(
        const std::vector<std::double_t>& a, const std::vector<std::double_t>& b,
        std::double_t eps = 1E-12);



}  // namespace apachee::fft