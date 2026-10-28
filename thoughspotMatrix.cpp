
#include <iostream>
#include <vector>
using namespace std;
const int MOD = 1e9 + 7;
// Function to multiply two 6x6 matrices
vector<vector<int>> multiply(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B
) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                C[i][j] = (C[i][j] +
                    1LL * A[i][k] * B[k][j] % MOD) % MOD;
            }
        }
    }

    return C;
}

// Function to compute (A^p) % MOD using binary exponentiation
vector<vector<int>> power(vector<vector<int>> A, long long p) {
    int n = A.size();
    vector<vector<int>> res(n, vector<int>(n, 0));

    // Initialize result as the Identity matrix
    for (int i = 0; i < n; ++i) {
        res[i][i] = 1;
    }

    while (p > 0) {
        if (p % 2 == 1) {
            res = multiply(res, A);
        }

        A = multiply(A, A);
        p /= 2;
    }

    return res;
}

long long getFn(long long n, long long a, long long b,
                long long c, long long d, long long e,
                long long f) {
    // Base case: F(x) = 1 for x <= 1
    if (n <= 1) return 1;

    // The 6x6 Transformation Matrix M
    vector<vector<int>> M = {
        {(int)(a % MOD), 0, 0, 0, (int)(b % MOD), 0},
        {0, (int)(c % MOD), 0, 0, 0, (int)(d % MOD)},
        {0, 0, (int)(e % MOD), (int)(f % MOD), 0, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0}
    };

    // Calculate M^(n-1)
    vector<vector<int>> M_pow = power(M, n - 1);

    long long ans = 0;

    // Sum the first row to obtain F(n)
    for (int i = 0; i < 6; ++i) {
        ans = (ans + M_pow[0][i]) % MOD;
    }

    return ans;
}
