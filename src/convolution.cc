#include <apachee/fft/convolution.h>

#include <vector>
#include <cmath>
#include <bit>
#include <complex>
#include <stdint.h>

#include <apachee/fft/internal/fft.hpp>

namespace apachee::fft {



std::vector<std::double_t>
convolution(
        const std::vector<std::double_t>& a_, const std::vector<std::double_t>& b_,
        std::double_t eps) {
    if (a_.empty() || b_.empty())
        return {};

    using complex_t = std::complex<std::double_t>;

    int64_t result_size = std::bit_ceil(a_.size() + b_.size() - 1);

    std::vector<complex_t> complex_result(a_.size());
    for (int64_t i = 0; i < a_.size(); i++)
        complex_result[i] = a_[i];

    complex_result.resize(result_size, 0);

    std::vector<complex_t> b(b_.size());
    for (int64_t i = 0; i < b_.size(); i++)
        b[i] = b_[i];
    b.resize(result_size, 0);

    internal::fft(complex_result.begin(), complex_result.end());
    internal::fft(b.begin(), b.end());

    for (int64_t i = 0; i < result_size; i++)
        complex_result[i] *= b[i];

    internal::fft(complex_result.begin(), complex_result.end(), true);
    while (complex_result.size() > 1 && abs(complex_result.back()) <= eps)
        complex_result.pop_back();

    std::vector<std::double_t> result(complex_result.size());
    for (int64_t i = 0; i < complex_result.size(); i++)
        result[i] = round(complex_result[i].real());

    return result;
}

std::vector<std::complex<std::double_t>>
complex_convolution(
        const std::vector<std::complex<std::double_t>>& a_, const std::vector<std::complex<std::double_t>>& b_,
        std::double_t eps) {
    if (a_.empty() || b_.empty())
        return {};

    using complex_t = std::complex<std::double_t>;

    int64_t result_size = std::bit_ceil(a_.size() + b_.size() - 1);

    std::vector<complex_t> complex_result(a_.size());
    for (int64_t i = 0; i < a_.size(); i++)
        complex_result[i] = a_[i];

    complex_result.resize(result_size, 0);

    std::vector<complex_t> b(b_.size());
    for (int64_t i = 0; i < b_.size(); i++)
        b[i] = b_[i];
    b.resize(result_size, 0);

    internal::fft(complex_result.begin(), complex_result.end());
    internal::fft(b.begin(), b.end());

    for (int64_t i = 0; i < result_size; i++)
        complex_result[i] *= b[i];

    internal::fft(complex_result.begin(), complex_result.end(), true);
    while (complex_result.size() > 1 && abs(complex_result.back()) <= eps)
        complex_result.pop_back();

    return complex_result;
}



}  // namespace apachee::fft