#include <bits/stdc++.h>
using namespace std;
struct BIT {
    int n; vector<int> t;
    BIT(int n) : n(n), t(n + 1) {}
    void add(int i, int d = 1) { for (++i; i <= n; i += i & -i) t[i] += d; }
    int sum(int i) { int s = 0; for (++i; i > 0; i -= i & -i) s += t[i]; return s; }
};
int main() {
     int n, k; cin >> n >> k;
    vector<int> a(n); for (auto &x : a) cin >> x;
    vector<int> tmp(a);                       // coordinate compression
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    vector<int> rnk(n);
    for (int i = 0; i < n; i++)
        rnk[i] = lower_bound(tmp.begin(), tmp.end(), a[i]) - tmp.begin();
    BIT bit(n);
    long long val = 0, ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        if (i - k >= 0) {                     // remove leftmost
            int r = rnk[i - k];
            bit.add(r, -1);
            val -= bit.sum(r - 1);            // smaller elements to its right
        }
        int r = rnk[i];                       // add rightmost
        bit.add(r);
        val += min(i + 1, k) - bit.sum(r);    // greater elements to its left
        if (i >= k - 1) ans = min(ans, val);
    }
    cout << ans << "\n";
}