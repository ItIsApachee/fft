#include <cmath>
#include <bit>
#include <stdint.h>

#include <apachee/fft.hpp>
#include "utils.hpp"

int main() {
    auto poly = polynomial_prompt("P");

    print_poly(poly, "P");

    std::cout << "DFT..." << std::endl;
    auto result = apachee::fft::dft(poly.begin(), poly.end());
    
    std::cout << "DFT: ";
    for (const auto &i : result) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    poly = apachee::fft::idft(result.begin(), result.end());
    print_poly(poly, "IDFT(DFT(P))");
    std::cout << std::endl;
}
