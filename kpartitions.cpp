#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumPenalty(vector<int>& arr, int k, int d) {
        int n = arr.size();

        if (k <= 0 || k > n) return -1;

        // Step 1: Precompute cost[i][j]
        // Penalty of subarray arr[i...j]
        vector<vector<long long>> cost(
            n, vector<long long>(n, 0)
        );

        for (int j = 1; j < n; j++) {
            long long cnt = 0;

            for (int i = j - 1; i >= 0; i--) {
                if ((long long)arr[i] - arr[j] > d) {
                    cnt++;
                }

                cost[i][j] = cost[i][j - 1] + cnt;
            }
        }

        // Step 2: Initialize DP
        const long long INF = LLONG_MAX / 4;

        // dp[g][i] = minimum penalty for first i elements
        // divided into exactly g non-empty groups
        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        dp[0][0] = 0;

        // Step 3: DP transitions
        for (int g = 1; g <= k; g++) {
            for (int i = g; i <= n; i++) {
                for (int j = i - 1; j >= g - 1; j--) {
                    if (dp[g - 1][j] == INF) continue;

                    dp[g][i] = min(
                        dp[g][i],
                        dp[g - 1][j] + cost[j][i - 1]
                    );
                }
            }
        }

        // Step 4: Return answer
        return dp[k][n];
    }
};
