#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    char kthCharacter(int n, vector<int>& ops, unsigned long long k) {
        // 0 -->simply append
        // 1 -->increase by one all char and append
        unsigned long long len = 1;

        // Length of string before every operation
        vector<unsigned long long> length(n);

        for (int i = 0; i < n; i++) {
            length[i] = len;
            len *= 2;
        }

        int shift = 0;

        // Go backwards through the operations
        for (int i = n - 1; i >= 0; i--) {

            // k lies in the second half
            if (k > length[i]) {

                k -= length[i];

                // Operation 1 increments every character
                if (ops[i] == 1) {
                    shift++;
                }
            }
        }

        shift %= 26;

        return char('a' + shift);
    }
};