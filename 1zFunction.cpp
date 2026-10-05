#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(string s) {
    
    int n = s.size();

    vector<int> z(n);

    int l = 0;
    int r = 0;

    for (int i = 1; i < n; i++) {

        if (i <= r){
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]){
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    string s, t;
    cin >> s >> t;

    string a = t + "#" + s;
    vector<int> z1 = zFunction(a);
    string rt = t;
    string rs = s;

    reverse(rt.begin(), rt.end());
    reverse(rs.begin(), rs.end());

    string b = rt + "#" + rs;

    vector<int> z2 = zFunction(b);

    int ans = 0;

    for (int i = 0; i <= n - m; i++) {
        int leftMatch = z1[m + 1 + i];
        leftMatch = min(leftMatch, m);
        if (leftMatch == m) {
            ans++;
            continue;
        }
        // First mismatch
        int p = leftMatch;
        if (p + 1 >= m)continue;
        if (s[i + p] != t[p + 1])
            continue;

        if (s[i + p + 1] != t[p])
            continue;
        int revStart = n - (i + m);

        int rightMatch = z2[m + 1 + revStart];

        rightMatch = min(rightMatch, m);

        int requiredSuffix = m - p - 2;

        if (rightMatch >= requiredSuffix) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}