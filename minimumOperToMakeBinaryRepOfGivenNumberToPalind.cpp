#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> pal;
    int givePalindrome(int num, int len){
        int ans = num;
        int temp = num;
        if(len % 2 == 1){
            temp = temp >> 1;
        }
        while(temp > 0){
            ans = (ans << 1) | (temp & 1);
            temp = temp >> 1;
        }
        return ans;
    }
    void binaryPalindromeGenerator(){
        for(int len = 1; len <= 31; len++){
            int half = (len + 1) / 2;
            int start = 1 << (half - 1);
            int end = 1 << half;
            for(int i = start; i < end; i++){
                int pn = givePalindrome(i, len);
                if(pn <= 1e6){
                    pal.push_back(pn);
                }
            }
        }
         sort(pal.begin(), pal.end());
    }
    vector<int> minOperations(vector<int>& nums) {
        binaryPalindromeGenerator();
        int n = nums.size();
        vector<int> ans(n, 0);
        for(int i = 0; i < n; i++){
            auto it = lower_bound(pal.begin(), pal.end(), nums[i]);
            if((*it == nums[i])) ans[i] = 0;
            else{
                int idx = it - pal.begin();
                ans[i] = pal[idx] - nums[i];
                if(idx - 1 >= 0){
                    ans[i] = min(pal[idx] - nums[i], nums[i] - pal[idx - 1]);
                }
            }
        }
        return ans;
    }
};