#include<bits/stdc++.h>
using namespace std;

class LCA {
public:
    vector<vector<int>> up;
    vector<int> depth;
    int cols;

    LCA(int n, vector<vector<int>>& adj, int root = 0) {
        cols = log2(n) + 1;

        up.resize(n, vector<int>(cols, -1));
        depth.resize(n);

        dfs(root, -1, adj);

        // Binary lifting table
        for (int j = 1; j < cols; j++) {
            for (int i = 0; i < n; i++) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    void dfs(int node, int parent, vector<vector<int>>& adj) {
        up[node][0] = parent;

        for (int child : adj[node]) {
            if (child == parent) continue;

            depth[child] = depth[node] + 1;
            dfs(child, node, adj);
        }
    }

    int getKthAncestor(int node, int k) {
        for (int j = 0; j < cols; j++) {
            if (k & (1 << j)) {
                node = up[node][j];

                if (node == -1)
                    return -1;
            }
        }

        return node;
    }

    int lca(int u, int v) {

        // Make depth[u] == depth[v]
        if (depth[u] > depth[v]) {
            u = getKthAncestor(u, depth[u] - depth[v]);
        }
        else {
            v = getKthAncestor(v, depth[v] - depth[u]);
        }

        // Same node
        if (u == v)
            return u;

        // Jump both upward
        for (int j = cols - 1; j >= 0; j--) {

            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }

        // Parent of both = LCA
        return up[u][0];
    }
};
int main(){

}