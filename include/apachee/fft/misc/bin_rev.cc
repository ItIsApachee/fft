vector<vector<int>> rev_precalc;

void rev_calc(int bits) {
    if (rev_precalc.size() <= bits)
        rev_precalc.resize(bits + 1);
    
    int n = 1 << bits;
    rev_precalc[bits].assign(n, 0);
    for (int i = 0, k = 1, f = (1 << (bits - 1)); i < bits; i++, k *= 2, f /= 2)
        for (int j = (1 << i); j < n; j += k)
            rev_precalc[bits][j] |= f;
    for (int i = 1; i < n; i++)
        rev_precalc[bits][i] ^= rev_precalc[bits][i - 1];
}