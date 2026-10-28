
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1000000007LL;

ll modpow(ll a, ll b) {
    ll res = 1;

    while (b > 0) {
        if (b & 1) {
            res = res * a % MOD;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

ll nCr(int n, int r, const vector<ll>& fact,
       const vector<ll>& invfact) {
    if (r < 0 || r > n || n < 0) return 0;

    return fact[n] * invfact[r] % MOD
         * invfact[n - r] % MOD;
}

ll solve(vector<int>& A) {
    int n = A.size();

    int C1 = 0;
    int M = 0;

    unordered_map<int, int> freq;

    for (int x : A) {
        freq[x]++;

        if (x == 1) {
            C1++;
        } else {
            M++;
        }
    }

    // All trays contain exactly one candy
    if (M == 0) {
        return (n % 2 == 1) ? 1 : 0;
    }

    // Precompute factorials and inverse factorials
    vector<ll> fact(n + 1), invfact(n + 1);

    fact[0] = 1;

    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    invfact[n] = modpow(fact[n], MOD - 2);

    for (int i = n - 1; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }

    // P_other = M! / product(freq[v]!) for v > 1
    ll P_other = fact[M];

    for (auto& [value, count] : freq) {
        if (value > 1) {
            P_other = P_other * invfact[count] % MOD;
        }
    }

    // Count permutations with an even number of leading ones
    ll sum = 0;

    for (int c = 0; c <= C1; c += 2) {
        sum = (sum + nCr(n - c - 1, M - 1,
                         fact, invfact)) % MOD;
    }

    return P_other * sum % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << solve(A) << '\n';

    return 0;
}
