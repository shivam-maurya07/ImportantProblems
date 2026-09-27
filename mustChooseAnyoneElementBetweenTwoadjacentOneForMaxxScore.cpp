#include <vector>
#include <algorithm>

using namespace std;

long long maximumPower(vector<int> &g) {
    int n = g.size();
    if (n == 0) return 0;
    
    // Create an N x 2 DP table initialized to 0
    // dp[i][0]: Max power up to index i, SKIPPING gemstone i
    // dp[i][1]: Max power up to index i, PICKING gemstone i
    vector<vector<long long>> dp(n, vector<long long>(2, 0));
    
    // Base cases for the very first gemstone (index 0)
    dp[0][0] = 0;         // Power is 0 if we skip it
    dp[0][1] = g[0];      // Power is g[0] if we pick it
    
    for (int i = 1; i < n; i++) {
        // State 0 (Skip current): We MUST have picked the previous gemstone
        dp[i][0] = dp[i - 1][1];
        
        // State 1 (Pick current): We take the best of either picking or skipping the previous gemstone, then add current
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + g[i];
    }
    
    // The final answer is the maximum of the two states at the very last index
    return max(dp[n - 1][0], dp[n - 1][1]);
}