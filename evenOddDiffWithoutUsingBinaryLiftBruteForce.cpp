#include<bits/stdc++.h>
using namespace std;

class solution{
public:
bool findPath(int u, int v, int parent,vector<vector<int>>& adj, vector<int>& path){
    if(u == v){
        path.push_back(v);
        return true;
    }
    for(auto neg : adj[u]){
        if(neg == parent) continue;
        if(findPath(neg, v, u, adj, path)){
            path.push_back(u);
            return true;
        }
    }
    return false;
}
long long partyGapAfterUpdates(
        int n,
        vector<long long>& a,
        vector<vector<int>>& edges,
        vector<vector<long long>>& queries
    ) {
        vector<vector<int>> adj(n + 1);
        for(auto x :edges){
            int u = x[0];
            int v = x[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }    
        for(auto q : queries){
            int u = q[0];
            int v = q[1];
            int x = q[2];
            vector<int> path;
            findPath(u, v, -1, adj, path);
            for(int i = 0; i < path.size(); i++){
                int node = path[i];
                a[node - 1] += x; 
            }
        }
        long long even = 0;
        long long odd = 0;
        for(int i = 0; i < a.size(); i++){
            if(a[i] % 2 == 0) even += a[i];
            else odd+=a[i];
        }
        return abs(even - odd);
    }
};