
#include <bits/stdc++.h>
using namespace std;
int maxTotalValue(vector<int>& a) {
    int n = a.size();

    int maxi = *max_element(a.begin(), a.end());

    vector<long long> sum(maxi + 1, 0);

    // Calculate total contribution of each value
    for (int x : a) {
        sum[x] += x;
    }

    vector<long long> dp(maxi + 1, 0);

    dp[0] = 0;

    if (maxi >= 1) {
        dp[1] = sum[1];
    }

    for (int i = 2; i <= maxi; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + sum[i]);
    }

    return dp[maxi];
}
