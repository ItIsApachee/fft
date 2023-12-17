#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <stdint.h>

#include <apachee/fft.hpp>
#include "utils.hpp"

void print_interpolation(const poly_t& poly, bool shorthand = false) {
    using namespace apachee::fft;

    if (poly.size() < 1) {
        throw std::domain_error("expected non-empty sequence");
    }

    auto coef = dft(poly.begin(), poly.end());

    std::double_t c = coef[0].real();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "P(x) = " << c;

    for (int64_t i = 1; i < coef.size(); i++) {
        std::double_t phase = std::arg(coef[i]);
        std::double_t amplitude = std::abs(coef[i]);

        // conversion from
        // amplitude * cos(i * x + phase)
        // to
        // a * cos(i * x) + b * sin(i * x)

        // cos(p + q) = cos(p) * cos(q) - sin(p) * sin(q)
        std::double_t a = std::cos(phase) * amplitude;
        std::double_t b = - std::sin(phase) * amplitude;
        {
            if (a >= 0) {
                std::cout << " + ";
            } else {
                std::cout << " - ";
            }
            std::cout << std::abs(a) << " * cos(2*pi*" << i << "/" << poly.size() << " * x)";
        }
        {
            if (b >= 0) {
                std::cout << " + ";
            } else {
                std::cout << " - ";
            }
            std::cout << std::abs(b) << " * sin(2*pi*" << i << "/" << poly.size() << " * x)";
        }
    }
}

int main() {

    int64_t n = 0;
    std::cout << "input number of values: ";
    std::cin >> n;

    poly_t poly(n);

    std::cout << std::fixed << std::setprecision(5);
    for (int64_t i = 0; i < n; i++) {
        // std::cout << "input P(" << arg << ") = P(" << i << " / " << n << "): ";
        std::cout << "input P(" << i << "): ";
        std::double_t v = 0;
        std::cin >> v;
        poly[i] = v;
    }

    print_interpolation(poly);
}