#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long solve(vector<vector<long long>>& dist) {

        int n = dist.size();

        // Step 1: Basic validation
        for (int i = 0; i < n; i++) {

            if (dist[i][i] != 0)
                return -1;

            for (int j = i + 1; j < n; j++) {

                if (dist[i][j] <= 0)
                    return -1;

                if (dist[i][j] != dist[j][i])
                    return -1;
            }
        }

        // Step 2: Prim's algorithm
        vector<bool> vis(n, false);

        // key[v] = minimum edge weight currently connecting v
        vector<long long> key(n, LLONG_MAX);

        // parent[v] = vertex through which v is connected
        vector<int> parent(n, -1);

        // {weight, node}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        key[0] = 0;
        pq.push({0, 0});

        long long ans = 0;
        int edgeCount = 0;

        // Store the constructed MST
        vector<vector<pair<int, long long>>> tree(n);

        while (!pq.empty()) {

            auto [w, u] = pq.top();
            pq.pop();

            if (vis[u])
                continue;

            vis[u] = true;

            // Add this edge to MST
            ans += w;

            if (parent[u] != -1) {

                int p = parent[u];

                tree[u].push_back({p, w});
                tree[p].push_back({u, w});

                edgeCount++;
            }

            // Update all possible edges from u
            for (int v = 0; v < n; v++) {

                if (!vis[v] && dist[u][v] < key[v]) {

                    key[v] = dist[u][v];
                    parent[v] = u;

                    pq.push({key[v], v});
                }
            }
        }

        // Could not form a tree
        if (edgeCount != n - 1)
            return -1;

        // Step 3: Verify the distances
        for (int src = 0; src < n; src++) {

            vector<long long> d(n, -1);

            queue<int> q;
            q.push(src);
            d[src] = 0;

            while (!q.empty()) {

                int u = q.front();
                q.pop();

                for (auto [v, w] : tree[u]) {

                    if (d[v] == -1) {

                        d[v] = d[u] + w;
                        q.push(v);
                    }
                }
            }

            // Compare calculated distances with given matrix
            for (int v = 0; v < n; v++) {

                if (d[v] != dist[src][v])
                    return -1;
            }
        }

        return ans;
    }
};