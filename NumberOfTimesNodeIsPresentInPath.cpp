#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int LOG = 20;

vector<int> adj[N];
int up[N][LOG];
int depth[N];
long long ans[N];

void dfs(int node, int parent) {
    up[node][0] = parent;

    for (int child : adj[node]) {
        if (child == parent)
            continue;

        depth[child] = depth[node] + 1;
        dfs(child, node);
    }
}

void build(int n) {
    dfs(1, -1);

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j - 1] != -1) {
                up[i][j] = up[up[i][j - 1]][j - 1];
            }
        }
    }
}

int getKthAncestor(int node, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            node = up[node][j];

            if (node == -1)
                return -1;
        }
    }

    return node;
}

int lca(int u, int v) {

    // Make depths equal
    if (depth[u] > depth[v]) {
        u = getKthAncestor(u, depth[u] - depth[v]);
    }
    else {
        v = getKthAncestor(v, depth[v] - depth[u]);
    }

    if (u == v)
        return u;

    // Lift both nodes
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }

    return up[u][0];
}

void dfsSum(int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent)
            continue;

        dfsSum(child, node);

        ans[node] += ans[child];
    }
}

vector<int> countPaths(
    int n,
    vector<vector<int>>& edges,
    vector<vector<int>>& paths
) {
    // Build adjacency list
    for (auto &e : edges) {
        int u = e[0];
        int v = e[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Binary lifting preprocessing
    build(n);

    // Process every path
    for (auto &p : paths) {
        int u = p[0];
        int v = p[1];

        int L = lca(u, v);

        ans[u]++;
        ans[v]++;
        ans[L]--;

        if (up[L][0] != -1)
            ans[up[L][0]]--;
    }

    // Accumulate from children to parents
    dfsSum(1, -1);

    vector<int> result(n);

    for (int i = 1; i <= n; i++) {
        result[i - 1] = ans[i];
    }

    return result;
}