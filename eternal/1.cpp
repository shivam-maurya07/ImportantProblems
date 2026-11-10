
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maxNutrition(vector<int>& price, vector<int>& nutrition, int M, int K) {
        int n = price.size();

        vector<vector<vector<int>>> dp(
            n + 1,
            vector<vector<int>>(M + 1, vector<int>(K + 1, 0))
        );

        for(int i = 1; i <= n; i++) {
            for(int j = 0; j <= M; j++) {
                for(int k = 0; k <= K; k++) {

                    // Don't buy current fruit
                    dp[i][j][k] = dp[i - 1][j][k];

                    // Buy at full price
                    if(j >= price[i - 1]) {
                        dp[i][j][k] = max(
                            dp[i][j][k],
                            dp[i - 1][j - price[i - 1]][k]
                            + nutrition[i - 1]
                        );
                    }

                    // Buy using coupon
                    int discountedPrice = price[i - 1] / 2;

                    if(k > 0 && j >= discountedPrice) {
                        dp[i][j][k] = max(
                            dp[i][j][k],
                            dp[i - 1][j - discountedPrice][k - 1]
                            + nutrition[i - 1]
                        );
                    }
                }
            }
        }

        return dp[n][M][K];
    }
};