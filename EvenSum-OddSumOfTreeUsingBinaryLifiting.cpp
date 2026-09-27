#include <bits/stdc++.h>
using namespace std;
class solution {
public:
    int LOG;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<long long> diff;

    void dfs(int node, int parent) {

        up[node][0] = parent;

        // Binary lifting table
        for(int j = 1; j < LOG; j++) {
            up[node][j] =
                up[up[node][j - 1]][j - 1];
        }

        for(int child : adj[node]) {

            if(child == parent)
                continue;

            depth[child] = depth[node] + 1;

            dfs(child, node);
        }
    }

    int LCA(int u, int v) {

        // Make u the deeper node
        if(depth[u] < depth[v])
            swap(u, v);

        // Bring u to same depth as v
        int d = depth[u] - depth[v];

        for(int j = 0; j < LOG; j++) {

            if(d & (1 << j)) {
                u = up[u][j];
            }
        }

        if(u == v)
            return u;

        // Lift both nodes
        for(int j = LOG - 1; j >= 0; j--) {

            if(up[u][j] != up[v][j]) {

                u = up[u][j];
                v = up[v][j];
            }
        }

        return up[u][0];
    }

    void accumulate(int node, int parent) {

        for(int child : adj[node]) {

            if(child == parent)
                continue;

            accumulate(child, node);

            diff[node] += diff[child];
        }
    }

    long long partyGapAfterUpdates(
        int n,
        vector<long long>& a,
        vector<vector<int>>& edges,
        vector<vector<long long>>& queries
    ) {

        LOG = log2(n) + 1;

        // Resize everything
        adj.resize(n + 1);
        up.resize(n + 1);
        depth.resize(n + 1);
        diff.resize(n + 1);

        for(int i = 0; i <= n; i++) {
            up[i].resize(LOG);
        }

        // Build tree
        for(auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Root tree at node 1
        dfs(1, 0);

        // Process queries
        for(auto &q : queries) {

            int u = q[0];
            int v = q[1];
            long long x = q[2];

            int L = LCA(u, v);

            diff[u] += x;
            diff[v] += x;

            diff[L] -= x;

            if(up[L][0] != 0) {
                diff[up[L][0]] -= x;
            }
        }

        // Propagate updates from children to parents
        accumulate(1, 0);

        long long even = 0;
        long long odd = 0;

        for(int i = 1; i <= n; i++) {

            long long value = a[i - 1] + diff[i];

            if(value % 2 == 0)
                even += value;
            else
                odd += value;
        }

        return llabs(even - odd);
    }
};