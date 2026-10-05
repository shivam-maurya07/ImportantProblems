#include <bits/stdc++.h>
using namespace std;

vector<int> zfunction(string s){
    int n = s.size();
    vector<int> z(n);
    int l = 0; 
    int r = 0;
    // if while if
    for(int i = 1; i < n; i++){
        // inside window
        if(i <= r){
            z[i] = min(r - i + 1, z[i - l]);
        }
        while((z[i] + i < n) && (s[z[i]] == s[z[i] + i])){
            z[i]++;
        }
        // outside window
        if((z[i] + i - 1) > r){
            l = i;
            r = z[i] + i - 1;
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
    int ans = 0;
    string a = t + "#" + s;
    vector<int> z1 = zfunction(a);
    string rs= s;
    string rt = t;
    reverse(rs.begin(), rs.end());
    reverse(rt.begin(), rt.end());

    string b =  rt + "#" + rs;
    vector<int> z2 = zfunction(b);

    for(int i = 0; i <= n - m; i++){
        int lmatch = z1[m + 1 + i];
        lmatch = min(lmatch, m);
        if(lmatch == m){
            ans ++;
            continue;
        }
        int p = lmatch;
        if(p + 1 >= m) continue;
        if(s[i + p] != t[p + 1]) continue;
        if(s[i + p + 1] != t[p]) continue;

        int revstart = n - (m + i);
        int rmatch = z2[m + 1 + revstart];
        rmatch = min(rmatch, m);
        if(rmatch >= m - p - 2){
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}