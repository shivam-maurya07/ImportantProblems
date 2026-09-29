#include <bits/stdc++.h>
using namespace std;

long long get_cost(int i, const vector<int>& threadSize) {
    long long target =
        max(threadSize[i - 1], threadSize[i + 1]) + 1LL;

    return max(0LL, target - threadSize[i]);
}

long long findMinIncrease(vector<int> threadSize) {
    int n = threadSize.size();

    if (n < 3)
        return 0;

    if (n % 2 == 1) {
        long long ans = 0;

        for (int i = 1; i < n - 1; i += 2) {
            ans += get_cost(i, threadSize);
        }

        return ans;
    }

    int k = (n - 2) / 2;

    vector<long long> cost_odd(k);
    vector<long long> cost_even(k);

    for (int i = 0; i < k; i++) {
        cost_odd[i] = get_cost(2 * i + 1, threadSize);
        cost_even[i] = get_cost(2 * i + 2, threadSize);
    }

    vector<long long> pref(k);
    vector<long long> suff(k);

    // Prefix sum of odd positions
    pref[0] = cost_odd[0];

    for (int i = 1; i < k; i++) {
        pref[i] = pref[i - 1] + cost_odd[i];
    }

    // Suffix sum of even positions
    suff[k - 1] = cost_even[k - 1];

    for (int i = k - 2; i >= 0; i--) {
        suff[i] = suff[i + 1] + cost_even[i];
    }

    long long ans = LLONG_MAX;

    // Take only even positions
    ans = min(ans, suff[0]);

    // Take only odd positions
    ans = min(ans, pref[k - 1]);

    // Take odd positions [0 ... i]
    // Take even positions [i+1 ... k-1]
    for (int i = 0; i < k - 1; i++) {
        ans = min(ans, pref[i] + suff[i + 1]);
    }

    return ans;
}