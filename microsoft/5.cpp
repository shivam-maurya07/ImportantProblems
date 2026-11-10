

#include <bits/stdc++.h>
using namespace std;
int countValidTokens(string tokenString) {
    stringstream ss(tokenString);
    string word;

    int ans = 0;

    while (ss >> word) {
        if (word.size() < 3) continue;

        bool vowel = false;
        bool consonant = false;
        bool valid = true;

        for (char ch : word) {

            if (!isalnum(ch)) {
                valid = false;
                break;
            }

            ch = tolower(ch);

            if (ch == 'a' || ch == 'e' || ch == 'i' ||
                ch == 'o' || ch == 'u') {
                vowel = true;
            }
            else if (isalpha(ch)) {
                consonant = true;
            }
        }

        if (valid && vowel && consonant) {
            ans++;
        }
    }

    return ans;
}
