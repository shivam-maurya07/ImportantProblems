#include <vector>
#include <cmath>
#include <algorithm>
// TERADATA

using namespace std;

const int MAXN = 100005;
const int LOG = 20;

// Global variables
vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];
long long ans[MAXN]; // Note: ans needs to be long long to prevent overflow from large query values

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
        if (up[u][j] != -1 && up[v][j] != -1 && up[u][j] != up[v][j]) {
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

long long solve(int N, vector<int> &A, vector<vector<int>> &edges, vector<vector<int>> &queries) {
    // CRITICAL: Reset global variables for multiple test case environments
    for (int i = 0; i <= N; i++) {
        adj[i].clear();
        depth[i] = 0;
        ans[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = -1;
        }
    }

    // Build adjacency list
    for (auto &e : edges) {
        int u = e[0];
        int v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Binary lifting preprocessing
    build(N);

    // Process every query using Tree Difference Array
    for (auto &q : queries) {
        int u = q[0];
        int v = q[1];
        long long x = q[2];

        int L = lca(u, v);

        ans[u] += x;
        ans[v] += x;
        ans[L] -= x;

        if (up[L][0] != -1)
            ans[up[L][0]] -= x;
    }

    // Accumulate from children to parents
    dfsSum(1, -1);

    long long sum_even = 0;
    long long sum_odd = 0;

    for (int i = 1; i <= N; i++) {
        // A is 0-indexed, but tree nodes are 1-indexed
        long long final_val = A[i - 1] + ans[i];
        
        // Proper negative modulo handling
        if (abs(final_val) % 2 == 0) {
            sum_even += final_val;
        } else {
            sum_odd += final_val;
        }
    }

    return abs(sum_even - sum_odd);
}