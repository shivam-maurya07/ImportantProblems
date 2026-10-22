
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static const long long MOD = 1000000007LL;

    long long digitPower(int p) {
        int evenSum = 0, oddSum = 0;

        while (p > 0) {
            int digit = p % 10;

            if (digit % 2 == 0) {
                evenSum += digit;
            } else {
                oddSum += digit;
            }

            p /= 10;
        }

        return abs(evenSum - oddSum);
    }

    int defeatingPower(int n) {
        long long ans = 0;

        for (int p = 2; p <= 2 * n; p++) {
            long long count;

            if (p <= n + 1) {
                count = p - 1;
            } else {
                count = 2LL * n + 1 - p;
            }

            long long power = digitPower(p);

            ans = (ans + (count * power) % MOD) % MOD;
        }

        return (int)ans;
    }
};
