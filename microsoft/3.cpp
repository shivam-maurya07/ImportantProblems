
#include <bits/stdc++.h>
using namespace std;
class DSU {
    vector<int> parent;
    vector<int> size;

public:
    DSU(int n) {
        size.resize(n + 1, 1);
        parent.resize(n + 1);

        for (int i = 0; i < n + 1; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }

    void UnionBySize(int a, int b) {
        int pa = find(a);
        int pb = find(b);

        if (pa == pb) return;

        if (size[pa] < size[pb]) {
            parent[pa] = pb;
            size[pb] += size[pa];
        }
        else {
            parent[pb] = pa;
            size[pa] += size[pb];
        }
    }
};

int minReplacements(string s, int k) {
    int n = s.size();

    DSU dsu(n);

    // Apply period and palindrome conditions
    for (int i = 0; i < n; i++) {

        // Period condition
        if (i + k < n) {
            dsu.UnionBySize(i, i + k);
        }

        // Palindrome condition
        dsu.UnionBySize(i, n - 1 - i);
    }

    // Build connected components
    vector<vector<int>> components(n);

    for (int i = 0; i < n; i++) {
        components[dsu.find(i)].push_back(i);
    }

    int ans = 0;

    // Calculate minimum replacements
    for (int i = 0; i < n; i++) {

        if (components[i].empty()) continue;

        vector<int> freq(26, 0);

        int mx = 0;

        for (int idx : components[i]) {
            freq[s[idx] - 'a']++;
            mx = max(mx, freq[s[idx] - 'a']);
        }

        int total = components[i].size();

        ans += total - mx;
    }

    return ans;
}
