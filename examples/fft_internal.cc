#include <cmath>
#include <bit>
#include <stdint.h>

// #include <apachee/fft/fft.hpp>
#include <apachee/fft/internal/fft.hpp>
#include "utils.hpp"

int main() {
    auto poly = polynomial_prompt("P");

    int64_t nearest_pow2 = std::bit_ceil(poly.size());
    poly.resize(nearest_pow2);
    std::cout << "size: " << nearest_pow2 << std::endl;

    print_poly(poly, "P");

    std::cout << "FFT..." << std::endl;
    apachee::fft::internal::fft(poly.begin(), poly.end());
    
    std::cout << "FFT: ";
    for (const auto &i : poly) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "InvFFT..." << std::endl;
    apachee::fft::internal::fft(poly.begin(), poly.end(), true);
    print_poly(poly, "P");
}