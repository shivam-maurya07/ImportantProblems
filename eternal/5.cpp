
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    long long countSubarrays(vector<int>& arr) {
        unordered_map<long long, long long> mp;

        mp[0] = 1;

        long long mask = 0;
        long long ans = 0;

        for(int x : arr) {
            int temp = x;
            long long curr = 0;

            for(int p = 2; p * p <= temp; p++) {
                int cnt = 0;

                while(temp % p == 0) {
                    cnt++;
                    temp /= p;
                }

                if(cnt % 2 == 1) {
                    curr ^= (1LL << p);
                }
            }

            if(temp > 1) {
                curr ^= (1LL << temp);
            }

            mask ^= curr;

            ans += mp[mask];

            mp[mask]++;
        }

        return ans;
    }
};