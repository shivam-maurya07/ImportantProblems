

#include <bits/stdc++.h>
using namespace std;
long long maxRequests(vector<int>& bandwidth,
                      vector<int>& request,
                      int totalBandwidth) {

    int n = bandwidth.size();

    vector<vector<long long>> dp(
        n + 1, vector<long long>(totalBandwidth + 1, 0)
    );

    for (int i = 1; i <= n; i++) {

        for (int w = 0; w <= totalBandwidth; w++) {

            // Do not select current endpoint
            dp[i][w] = dp[i - 1][w];

            // Select current endpoint
            if (w >= bandwidth[i - 1]) {

                dp[i][w] = max(
                    dp[i][w],
                    dp[i - 1][w - bandwidth[i - 1]]
                    + request[i - 1]
                );
            }
        }
    }

    return dp[n][totalBandwidth];
}
