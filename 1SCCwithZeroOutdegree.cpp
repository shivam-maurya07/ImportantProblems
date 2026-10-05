#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    void dfs(int node, vector<vector<int>> &adj, stack<int>& st,vector<int>& vis){
        vis[node] = 1;
        for(auto neg: adj[node]){
            if(!vis[neg]){
                dfs(neg, adj, st, vis);
            }
        }
        st.push(node);
    }
    void dfs2(int node, vector<vector<int>> &adj, vector<int>& comp,vector<int>& vis, int &cc){
        vis[node] = 1;
        comp[node] = cc;
        for(auto neg: adj[node]){
            if(!vis[neg]){
                dfs2(neg, adj, comp, vis,cc);
            }
        }
    }
    int minRestart(vector<vector<int>> &adj) {
        // adj size is n + 1
        int n = adj.size() - 1;
        vector<int> vis(n + 1, 0);
        stack<int> st;

        // forward propagation
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                dfs(i, adj,st,vis);
            }
        }
        vector<vector<int>> radj(n + 1);
        // backward propagtion
        for(int i = 1; i <=n; i++){
            vis[i] = 0;
            for(auto neg: adj[i]){
                radj[neg].push_back(i);
            }
        }
        vector<int> comp(n + 1, -1);
        int cc = 0;
        while(!st.empty()){
            int node = st.top();
            st.pop();
            if(!vis[node]){
                cc ++;
                dfs2(node, radj,comp,vis, cc);
            }
        }
        vector<int> out(cc+1, 0);
        for(int i = 1; i <= n; i++){
            for(auto neg : adj[i]){
                if(comp[neg] != comp[i]){
                    out[comp[neg]] = 1;
                }
            }
        }
        int ans = 0;
        for(int i = 1; i <= cc; i++){
            if(out[i] == 0){
                ans++;
            }
        }
        return ans;
    }
};