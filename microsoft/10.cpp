
#include <bits/stdc++.h>
using namespace std;
int solve(int n, int d, vector<int>& trails) {
    if(d > n) return -1;

    const int INF = 1e9;

    vector<vector<int>> dp(d + 1, vector<int>(n + 1, INF));

    dp[0][0] = 0;

    for(int i = 1; i <= d; i++) {
        for(int j = i; j <= n; j++) {

            int maxi = 0;

            for(int k = j; k >= i; k--) {
                maxi = max(maxi, trails[k - 1]);

                dp[i][j] = min(dp[i][j],
                               dp[i - 1][k - 1] + maxi);
            }
        }
    }

    return dp[d][n] == INF ? -1 : dp[d][n];
}
