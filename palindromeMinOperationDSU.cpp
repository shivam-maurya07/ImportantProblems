#include <bits/stdc++.h>
using namespace std;

class DSU {
public:
    vector<int> parent, size;

    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);

        for(int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if(node == parent[node])
            return node;

        return parent[node] = find(parent[node]);
    }

    void unionBySize(int u, int v) {

        int pu = find(u);
        int pv = find(v);

        if(pu == pv)
            return;

        if(size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

class Solution {
public:
    int getMinOperations(vector<int> data) {

        int n = data.size();

        // Coordinate compression
        unordered_map<int, int> mp;

        int id = 0;

        for(int i = 0; i < n; i++) {

            if(mp.find(data[i]) == mp.end()) {
                mp[data[i]] = id++;
            }

            data[i] = mp[data[i]];
        }

        // IDs are 0 to id-1
        DSU dsu(id);

        // Union values which are mirror pairs
        for(int i = 0; i < n / 2; i++) {

            int j = n - i - 1;

            if(data[i] != data[j]) {
                dsu.unionBySize(data[i], data[j]);
            }
        }

        // Count distinct values in every component
        vector<int> cnt(id, 0);

        for(auto x : mp) {

            int node = x.second;

            cnt[dsu.find(node)]++;
        }

        // A component with k values requires k-1 operations
        int ans = 0;

        for(int i = 0; i < id; i++) {

            if(cnt[i] > 0) {
                ans += cnt[i] - 1;
            }
        }

        return ans;
    }
};