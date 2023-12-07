#include <complex>
#include <cmath>

namespace apachee::fft {

using base_float = std::double_t;
// using base_t = std::complex<base_float>;

base_float PI = std::acos(-1);

template<typename RandomIt>
void fft(RandomIt first, RandomIt last, bool inverse = false) {
    RandomIt& a = first;
    int n = last - first;

    // TODO: rewrite for iterators [first; last)
    // TODO: last - first != 2^k
    // assert((1 << __lg(a.size())) == a.size());

    int n = a.size();

    // use std::countl_zero 
    int n_bits = __lg(n); // FIXME: make cross-platform

    rev_calc(n_bits);
    for (int i = 0; i < n; i++) {
        auto i_rev = rev_precalc[n_bits][i];
        if (i < i_rev)
            swap(a[i], a[i_rev]);
    }

    for (int k = 2; k <= n; k *= 2) {
        int k_half = k / 2;

        base_float power = 2 * (inverse ? -1 : 1) * PI / k;
        std::complex<base_float> w0 = exp(std::complex<base_float>{0.0L, power});
        for (int i = 0; i < n; i += k) {
            std::complex<base_float> w = 1;
            for (int j = 0; j < k_half; j++, w *= w0) {
                std::complex<base_float> x = a[i + j], y = a[i + j + k_half];
                y *= w;
                a[i + j] = x + y, a[i + j + k_half] = x - y;
            }
        }
    }

    if (inverse) {
        for (int i = 0; i < n; i++)
            a[i] /= n;
    }
}

}  // namespace apachee::fft
