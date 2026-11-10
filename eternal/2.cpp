
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> adj;
    vector<int> sub;

    void dfs(int u, int p) {
        sub[u] = 1;

        for (int v : adj[u]) {
            if (v == p) continue;

            dfs(v, u);
            sub[u] += sub[v];
        }
    }

    long long countTriplets(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        sub.resize(n, 0);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(0, -1);

        long long collinear = 0;

        for (int u = 0; u < n; u++) {
            long long sum = 0;

            for (int v : adj[u]) {
                long long sz;

                if (sub[v] < sub[u]) {
                    sz = n - sub[u];
                }
                else {
                    sz = sub[v];
                }

                collinear += sum * sz;
                sum += sz;
            }
        }

        long long total = 1LL * n * (n - 1) * (n - 2) / 6;

        return total - collinear;
    }
};
