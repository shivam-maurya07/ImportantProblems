#include<bits/stdc++.h>
using namespace std;
void dfs(int node,int p, vector<vector<int>> & adj, vector<int>& sz){
    // bottom up approach
    sz[node] = 1;
    for(auto x : adj[node]){
        if(x == p) continue;
        dfs(x, node,adj,sz);
        sz[node] += sz[x];
    }
}
int maxEdgesremoved(int n, vector<vector<int>> & adj){
    if(n % 2 == 1) return -1;
    vector<int> sz(n + 1);
    dfs(1, 0, adj, sz);
    int cnt = 0;
    for(int i = 2; i <= n; i++){
        if((sz[i] % 2) == 0) cnt++;
    }
    return cnt;
}
int main(){

}