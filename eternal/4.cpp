
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int best_desk_to_wipe(int n, vector<vector<int>>& link, vector<int>& seeded) {
        vector<int> vis(n, 0);
        vector<int> comp(n, -1);
        vector<int> sz;

        int id = 0;

        // Find connected components using BFS
        for(int i = 0; i < n; i++) {
            if(vis[i]) continue;

            queue<int> q;
            q.push(i);
            vis[i] = 1;

            int cnt = 0;

            while(!q.empty()) {
                int u = q.front();
                q.pop();

                comp[u] = id;
                cnt++;

                for(int v = 0; v < n; v++) {
                    if(link[u][v] == 1 && !vis[v]) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }

            sz.push_back(cnt);
            id++;
        }

        // Count seeded desks in each component
        vector<int> infected(id, 0);

        for(int x : seeded) {
            infected[comp[x]]++;
        }

        // Find the best desk to remove
        int ans = seeded[0];
        int maxSaved = -1;

        for(int x : seeded) {
            int c = comp[x];

            int saved = 0;

            if(infected[c] == 1) {
                saved = sz[c];
            }

            if(saved > maxSaved || (saved == maxSaved && x < ans)) {
                maxSaved = saved;
                ans = x;
            }
        }

        return ans;
    }
};