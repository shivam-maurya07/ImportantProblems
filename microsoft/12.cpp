
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> maxItems(vector<int>& prices, vector<vector<int>>& queries) {
        int n = prices.size();

        vector<long long> pref(n);

        pref[0] = prices[0];

        for (int i = 1; i < n; i++) {
            pref[i] = pref[i - 1] + prices[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int start = q[0];
            long long budget = q[1];

            long long before = (start == 0 ? 0 : pref[start - 1]);
            long long target = before + budget;

            auto it = upper_bound(pref.begin() + start, pref.end(), target);

            int idx = it - pref.begin();

            ans.push_back(idx - start);
        }

        return ans;
    }
};
