#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Optimize standard I/O operations for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string S, T;
    if (cin >> S >> T) {
        bool has_black = false;
        bool has_white = false;
        
        // Check the available colors in string S
        for (char c : S) {
            if (T[c - 'a'] == 'B') {
                has_black = true;
            } else {
                has_white = true;
            }
            
            // Early exit for the loop if both colors are found
            if (has_black && has_white) {
                break;
            }
        }
        
        // If we have at least one of each color, we can sort the entire string
        if (has_black && has_white) {
            sort(S.begin(), S.end());
        }
        
        cout << S << "\n";
    }
    
    return 0;
}