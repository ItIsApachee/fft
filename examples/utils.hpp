#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <ios>
#include <stdint.h>

#pragma once

void init_io() {
    using ios_base = std::ios_base;
    std::cin.exceptions(ios_base::badbit | ios_base::failbit);
    std::cout.exceptions(ios_base::badbit | ios_base::failbit);
}

using poly_t = std::vector<std::complex<std::double_t>>;

poly_t polynomial_prompt(const std::string& poly_name) {
    std::cout << "Prompting for polynomial " << poly_name << "(x)" << std::endl;
    std::cout << "Enter degree of \"" << poly_name << "\": ";

    int64_t deg = 0;
    std::cin >> deg;

    std::vector<std::complex<std::double_t>> poly(deg + 1);

    std::cout << "Enter coeficients:" << std::endl;

    for (int64_t i = 0; i <= deg; i++) {
        if (i == 0) {
            std::cout << "1: ";
        } else if (i == 1) {
            std::cout << "x: ";
        } else {
            std::cout << "x ^ " << i << ": ";
        }

        std::double_t x = 0;
        std::cin >> x;
        poly[i] = x;
    }

    return poly;
}

void print_poly(const poly_t& poly, std::string poly_name = "") {
    constexpr std::double_t EPS = 1e-12;

    if (poly_name == "") {
        poly_name = "<unnamed>";
    }
    std::cout << "Polynomial " << poly_name << "(x) = ";

    if (poly.empty()) {
        std::cout << 0 << std::endl;
        return;
    }

    int64_t deg = poly.size() - 1;

    bool has_prev = false;
    for (int64_t i = 0; i <= deg; i++) {
        if (std::abs(poly[i]) < EPS)
            continue;
        
        if (has_prev) {
            std::cout << " + ";
        } else {
            has_prev = true;
        }

        std::cout << poly[i];
        if (i == 1) {
            std::cout << " * x";
        } else if (i > 1) {
            std::cout << " * x ^ " << i;
        }
    }

    // everything is 0
    if (!has_prev)
        std::cout << 0;
    std::cout << std::endl;
}