#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool prime(int n){
        if (n <= 1) return false;
        for(int i = 2; i* i <= n; i++){
            if(n % i == 0) return false;
        }
    return true;
    }
    int minOperations(int n, int m) {
        if (prime(n)) return -1;
        vector<int> dist(1e4+1, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
        dist[n] = n;
        q.push({n, n});

        while(!q.empty()){
            auto [d,curr] = q.top(); // curr.first = dist, curr.second = node
            q.pop();
            if(curr == m) return dist[curr];
            string s = to_string(curr);
            string temp = s;

            for(int i = 0; i < temp.size(); i++){
                int x = (temp[i] - '0');
                if(x == 9) continue;
                temp[i]++;
                if(!prime(stoi(temp))){
                    if(dist[stoi(temp)] > dist[curr] + stoi(temp)){
                        q.push({dist[curr] + stoi(temp),stoi(temp)});
                        dist[stoi(temp)] = dist[curr] + stoi(temp);
                    }
                }
                temp = s;
            }
            for(int i = 0; i < temp.size(); i++){
                int x = (temp[i] - '0');
                if(x == 0) continue;
                temp[i]--;
                if(!prime(stoi(temp))){
                if(dist[stoi(temp)] > dist[curr] + stoi(temp)){
                    dist[stoi(temp)] = dist[curr] + stoi(temp);
                    q.push({dist[curr] + stoi(temp),stoi(temp)});
                }
                }
                temp = s;
            }

        }
        return dist[m] == INT_MAX ? -1 : dist[m];
    }
};