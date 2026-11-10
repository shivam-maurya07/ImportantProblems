
#include <bits/stdc++.h>
using namespace std;
long long countPairs(vector<string>& s) {
    unordered_map<int, long long> mp;
    long long ans = 0;

    for (string &str : s) {
        int mask = 0;

        for (char ch : str) {
            mask ^= (1 << (ch - 'a'));
        }

        // Case 1: Same mask
        ans += mp[mask];

        // Case 2: Differ by exactly one bit
        for (int i = 0; i < 26; i++) {
            int newMask = mask ^ (1 << i);
            ans += mp[newMask];
        }

        // Insert current mask
        mp[mask]++;
    }

    return ans;
}
