#include<bits/stdc++.h>
using namespace std;

class solution{
public:

long long minCostWithBannedTurns(long long n, vector<vector<long long>>& edges, vector<vector<long long>>& banned, long long src, long long t){
        vector<vector<pair<long long,long long>>> adj(n + 1);
        if(src == t) return 0;
        for(long long i = 0; i < edges.size(); i++){
            long long u = edges[i][0];
            long long v = edges[i][1];
            long long w = edges[i][2];
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        unordered_set<long long> st;
        for(long long i = 0; i < banned.size(); i++){
            long long a = banned[i][0];
            long long b = banned[i][1];
            long long c = banned[i][2];
            long long num = (a * 1LL*(n + 1) * 1LL*(n + 1)) + (b * (n + 1)) + (c);
            st.insert(num);

        }
        vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, 1LL << 62));
        priority_queue<vector<long long>,vector<vector<long long>>, greater<vector<long long>>> pq;

        for(auto x : adj[src]){
            if(x.second < dist[src][x.first]){
                dist[src][x.first] = x.second;
                 pq.push({x.second, src, x.first});
            }
        }

        while(!pq.empty()){
            auto x = pq.top();
            pq.pop();
            long long currWt = x[0];
            long long a = x[1];
            long long b = x[2];

            if(dist[a][b] != currWt) continue; // extra
            if(b == t) return currWt;
            
            for(auto neg : adj[b]){
                long long wt = neg.second;
                long long c = neg.first;
                if(st.count((a * 1LL*(n + 1) * 1LL*(n + 1)) + (b * (n + 1)) + (c))){
                    continue;
                }
                if(currWt + wt < dist[b][c]){
                    dist[b][c] = currWt + wt;
                    pq.push({currWt + wt, b, c});
                }

            }
        }
        return -1;

    }
};