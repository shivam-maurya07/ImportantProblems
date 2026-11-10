
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<int> dp, ans;
vector<vector<int>> adj;

void dfs1(int u, int p) {
    dp[u] = (a[u] == 1 ? 1 : -1);

    for (int v : adj[u]) {
        if (v == p) continue;

        dfs1(v, u);

        dp[u] += max(0, dp[v]);
    }
}
void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;

        ans[v] = dp[v] + max(0, ans[u] - max(0, dp[v]));

        dfs2(v, u);
    }
}

int main() {
    cin >> n;

    a.resize(n);
    dp.resize(n);
    ans.resize(n);
    adj.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(0, -1);

    ans[0] = dp[0];

    dfs2(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
