#include <bits/stdc++.h>
using namespace std;
long long maxConstrainedSubarraySum(vector<int>& arr, int d) {
    int n = arr.size();

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
        pref[i + 1] = pref[i] + arr[i];

    deque<int> mx, mn, ps;
    int left = 0;
    long long ans = LLONG_MIN;

    for (int right = 0; right < n; right++) {
        while (!mx.empty() && arr[mx.back()] <= arr[right])
            mx.pop_back();
        mx.push_back(right);

        while (!mn.empty() && arr[mn.back()] >= arr[right])
            mn.pop_back();
        mn.push_back(right);

        while ((long long)arr[mx.front()] - arr[mn.front()] > d) {
            if (mx.front() == left)
                mx.pop_front();
            if (mn.front() == left)
                mn.pop_front();
            left++;
        }

        while (!ps.empty() && ps.front() < left)
            ps.pop_front();

        while (!ps.empty() && pref[ps.back()] >= pref[right])
            ps.pop_back();
        ps.push_back(right);

        ans = max(ans, pref[right + 1] - pref[ps.front()]);
    }

    return ans;
}