#include <bits/stdc++.h>
using namespace std;

class solution {
public:

    int LOG;

    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<long long> diff;

    void dfs(int u, int parent) {

        up[0][u] = parent;

        for(int j = 1; j < LOG; j++) {
            up[j][u] = up[j - 1][up[j - 1][u]];
        }

        for(int v : adj[u]) {

            if(v == parent)
                continue;

            depth[v] = depth[u] + 1;

            dfs(v, u);
        }
    }

    int lca(int u, int v) {

        // Make u the deeper node
        if(depth[u] < depth[v])
            swap(u, v);

        // Bring u to same depth as v
        int difference = depth[u] - depth[v];

        for(int j = 0; j < LOG; j++) {

            if(difference & (1 << j)) {
                u = up[j][u];
            }
        }

        if(u == v)
            return u;

        // Lift both nodes
        for(int j = LOG - 1; j >= 0; j--) {

            if(up[j][u] != up[j][v]) {

                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

    void accumulate(int u, int parent, vector<long long>& a) {

        for(int v : adj[u]) {

            if(v == parent)
                continue;

            accumulate(v, u, a);

            diff[u] += diff[v];
        }
    }

    long long partyGapAfterUpdates(
        int n,
        vector<long long>& a,
        vector<vector<int>>& edges,
        vector<vector<long long>>& queries
    ) {

        adj.assign(n + 1, {});

        // Build tree
        for(auto e : edges) {

            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // log2(n)
        LOG = 1;

        while((1 << LOG) <= n)
            LOG++;

        up.assign(LOG, vector<int>(n + 1, 0));
        depth.assign(n + 1, 0);
        diff.assign(n + 1, 0);

        // Root tree at node 1
        dfs(1, 0);

        // Process queries
        for(auto q : queries) {

            int u = q[0];
            int v = q[1];

            long long x = q[2];

            int L = lca(u, v);

            diff[u] += x;
            diff[v] += x;

            diff[L] -= x;

            // Remove contribution from above LCA
            if(up[0][L] != 0)
                diff[up[0][L]] -= x;
        }

        // Accumulate updates from children to parents
        accumulate(1, 0, a);

        long long even = 0;
        long long odd = 0;

        for(int i = 1; i <= n; i++) {

            long long finalValue = a[i - 1] + diff[i];

            if(finalValue % 2 == 0)
                even += finalValue;
            else
                odd += finalValue;
        }

        return llabs(even - odd);
    }
};