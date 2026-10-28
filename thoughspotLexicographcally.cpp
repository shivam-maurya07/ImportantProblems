#include <iostream>
#include <string>
#include <vector>

using namespace std;

string getLargestString(string S, long long K) {
    int n = S.length();
    
    // pref[i] stores the total deletion cost of characters from S[0] to S[i-1]
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + (S[i] - 'a' + 1);
    }

    // next_pos[i][c] stores the earliest index >= i where character 'a'+c appears.
    // -1 if it never appears again.
    vector<vector<int>> next_pos(n + 1, vector<int>(26, -1));
    
    for (int i = n - 1; i >= 0; i--) {
        for (int c = 0; c < 26; c++) {
            next_pos[i][c] = next_pos[i + 1][c];
        }
        // Update the occurrence of the current character
        next_pos[i][S[i] - 'a'] = i;
    }

    string ans = "";
    int curr = 0;
    
    // Build the string greedily
    while (curr < n) {
        // Try characters from 'z' (25) down to 'a' (0)
        for (int c = 25; c >= 0; c--) {
            int j = next_pos[curr][c];
            
            if (j != -1) {
                // Cost to skip all characters strictly between curr and j
                long long cost = pref[j] - pref[curr];
                
                // If we have enough budget to delete the skipped characters
                if (cost <= K) {
                    ans += (char)('a' + c);
                    K -= cost;         // Deduct the cost from our budget
                    curr = j + 1;      // Move our pointer right past the picked character
                    break;             // Break to start looking for the next character
                }
            }
        }
    }
    
    return ans;
}

