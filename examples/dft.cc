#include <cmath>
#include <bit>
#include <stdint.h>

#include <apachee/fft.hpp>
#include "utils.hpp"

int main() {
    auto poly = polynomial_prompt("P");

    print_poly(poly, "P");

    std::cout << "DFT..." << std::endl;
    auto result = apachee::fft::discrete_fourier_transform(poly.begin(), poly.end());
    
    std::cout << "DFT: ";
    for (const auto &i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
