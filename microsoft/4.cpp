#include<bits/stdc++.h>
using namespace std;
int minimumK(vector<int>& arr) {
    int n = arr.size();

    // Root must be the maximum element
    for (int i = 1; i < n; i++) {
        if (arr[0] < arr[i]) {
            return -1;
        }
    }

    for (int k = 1; k < n; k++) {
        bool valid = true;

        for (int i = 0; i < n; i++) {

            int start = k * i + 1;
            int end = min(n - 1, k * i + k);

            for (int j = start; j <= end; j++) {
                if (arr[i] < arr[j]) {
                    valid = false;
                    break;
                }
            }

            if (!valid) break;
        }

        if (valid) return k;
    }

    return -1;
}
