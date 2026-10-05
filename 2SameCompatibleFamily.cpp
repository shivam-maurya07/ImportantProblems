#include <bits/stdc++.h>
using namespace std;
bool compatible(string x, string y) {
    if (abs((int)x.size() - (int)y.size()) > 1)
        return false;
    int freq[26] = {};
    for (char c : x)
        freq[c - 'A']++;
    for (char c : y)
        freq[c - 'A']--;
    int positive = 0, negative = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0)
            positive += freq[i];

        if (freq[i] < 0)
            negative -= freq[i];
    }
    if (x.size() == y.size())
        return positive == 0 && negative == 0;
    return positive + negative == 1;
}
vector<vector<string>> groupMoldFamilies(const vector<string>& codes) {
    // Write your code here.
    // Return the families; each family lists its codes in input order.
    int n = codes.size();
    vector<vector<string>> ans;
    ans.push_back({codes[0]});
    for(int i = 1; i < n; i++){
        bool flag = false;
        for(auto &st : ans){
            vector<string> temp = st;
            for(auto &s : temp){
                 string x = codes[i];
                 string y = s;
                 if(compatible(x, y)){
                    st.push_back(x);
                    flag = true;
                    break;
                 }
            }
            if(flag) break;
        }
        if(flag == false) ans.push_back({codes[i]});
    }
    return ans;
}