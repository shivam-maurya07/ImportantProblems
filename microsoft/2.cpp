
#include <bits/stdc++.h>
using namespace std;
int maxValleys(vector<int>& arr) {
    sort(arr.begin(), arr.end());

    int n = arr.size();
    int i = 0;
    int j = (n + 1) / 2;
    int ans = 0;

    while (i < n / 2 && j < n) {
        if (arr[i] < arr[j]) {
            ans++;
            i++;
            j++;
        }
        else {
            j++;
        }
    }

    return ans;
}
