#pragma once

#define N_CORNERS 8
#define N_EDGES 12

inline unsigned int binomial(int n, int k) {
    if (k == 0 || k == n) {
        return 1;
    }
   return binomial(n - 1, k - 1) + binomial(n - 1, k);
}