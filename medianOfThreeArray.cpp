#include <bits/stdc++.h>
using namespace std;
int kth(vector<int>& A, vector<int>& B, vector<int>& C, int k) {

    int low = min({A[0], B[0], C[0]});
    int high = max({A.back(), B.back(), C.back()});

    int ans = -1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        int cnt =
            upper_bound(A.begin(), A.end(), mid) - A.begin()
            + upper_bound(B.begin(), B.end(), mid) - B.begin()
            + upper_bound(C.begin(), C.end(), mid) - C.begin();

        if (cnt >= k) {
            ans = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    return ans;
}
double medianThree(vector<int>& A, vector<int>& B, vector<int>& C) {

    int n = A.size() + B.size() + C.size();

    int k1 = (n + 1) / 2;
    int k2 = (n + 2) / 2;

    long long x = kth(A, B, C, k1);
    long long y = kth(A, B, C, k2);

    return (x + y) / 2.0;
}