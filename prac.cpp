#include<bits/stdc++.h>
using namespace std;

string f(string s, long long b){
    long long n = s.size();
    vector<long long> pref(n + 1);
    for(long long i = 0; i < n; i++){
        pref[i + 1] = pref[i] + s[i] - 'a' + 1;
    }
    vector<vector<long long>> firstocc(n+ 1, vector<long long>(26, -1));
    for(long long i = n-1; i >= 0; i--){
        for(long long c = 0; c < 26; c++){
            firstocc[i][c] = firstocc[i + 1][c];
        }
        firstocc[i][s[i] - 'a'] = i;
    }
    string ans = "";
    long long curr = 0;

    while(curr < n){
          bool found = false;
        for(long long i = 25; i >= 0; i--){
            long long j = firstocc[curr][i];

            if(j != -1){
                long long cost = pref[j] - pref[curr];
                if(b >= cost){
                    b-=cost;
                    ans+= char(i + 'a');
                    curr = j + 1;
                    break;
                }

            }
        }
    }
    return ans;

}