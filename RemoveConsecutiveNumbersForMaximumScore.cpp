#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    int f(int l, int r, int k, vector<int>& arr, vector<vector<vector<int>>>& dp){
        if(l > r) return 0; // base case

        if(dp[l][r][k] != -1) return dp[l][r][k]; // memo

        // option 1
        int ans = f(l, r - 1, 0, arr, dp) + ((k + 1) * (k + 1));
        // option 2
        for(int i = l; i < r; i++){
            if(arr[i] == arr[r]){
                ans = max(ans, f(l, i, k + 1, arr, dp) + f(i + 1, r - 1, 0, arr, dp));
            }
        }
        return dp[l][r][k] = ans;
    }
    int removeBoxes(vector<int>& boxes) {
        int n = boxes.size();
        vector<int> arr = boxes;
        int m = arr.size();
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(m + 1, vector<int>(m + 1, -1)));
        return f(0, m - 1, 0, arr, dp);

    }
};