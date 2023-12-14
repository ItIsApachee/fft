#include <cmath>
#include <numbers>

#include <apachee/fft/fft.hpp>
#include "utils.hpp"

int main() {
    auto poly = polynomial_prompt("P");
    print_poly(poly, "P");

    double_t phi = 0;
    std::cout << "enter phi for C = e^{i * \\pi * phi} for CZT: ";
    std::cin >> phi;
    auto pi = std::numbers::pi_v<std::double_t>;
    std::complex<std::double_t> C = std::exp(std::complex<std::double_t>{0, pi * phi});

    auto result = apachee::fft::chirp_z_transform(poly.begin(), poly.end(), C);

    for (int64_t i = 0; i < result.size(); i++) {
        std::cout << "P(" << std::pow(C, i) << ") = " << result[i] << std::endl;
    }
}