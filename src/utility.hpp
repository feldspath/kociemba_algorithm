#pragma once

#define N_CORNERS 8
#define N_EDGES 12
#define N_SLICE 4
#define N_MOVES 18

#include <array>
#include <math.h>
#include <set>

inline unsigned int binomial(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
   return binomial(n - 1, k - 1) + binomial(n - 1, k);
}

template <size_t N>
unsigned int factorial_coord(std::array<int, N> values) {
    static_assert(N <= 12);
    unsigned int coord = 0;
    unsigned int mult = 1;
    for (size_t c = 1; c < values.size(); ++c) {
        mult *= c;
        int inf_count = 0;
        for (size_t d = 0; d < c; ++d) {
            if (values[N-1-d] < values[N-1-c]) ++inf_count;
        }
        coord += mult * inf_count;
    }
    return coord;
}

inline unsigned int factorial(unsigned int n) {
    if (n <= 1) return 1;
    return factorial(n-1) * n;
}

template <size_t N>
std::array<int, N> inverse_factorial_coord(unsigned int value) {
    std::array<int, N> output;
    unsigned int mult = factorial(N-1);
    for (size_t c = 0; c < N; ++c) {
        int inf_count = c == N-1 ? 0 : value / mult;
        value -= mult * inf_count;
        std::set<int> sup_set;
        sup_set.insert(output.begin(), output.begin()+c);
        for (const auto& v : sup_set) {
            if (v <= inf_count) ++inf_count;
        }
        output[c] = inf_count;
        if (c < N-1) mult /= (N-1-c);
    }
    return output;
}