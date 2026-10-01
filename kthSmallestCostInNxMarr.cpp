#include <bits/stdc++.h>
using namespace std;

long long countPairs(const vector<long long>& X,
                     const vector<long long>& Y,
                     long long mid) {

    long long cnt = 0;

    for (int i = 0; i < X.size(); i++) {

        long long val = mid - X[i];

        cnt += upper_bound(Y.begin(), Y.end(), val) - Y.begin();
    }

    return cnt;
}

long long kthCheapestPairing(
    int N, int M, long long K,
    long long X0, long long Ax, long long Bx, long long Cx,
    long long Y0, long long Ay, long long By, long long Cy
) {

    vector<long long> X(N);
    vector<long long> Y(M);

    X[0] = X0;

    for (int i = 1; i < N; i++) {
        X[i] = X[i - 1] +
               ((long long)i * Ax + Bx) % Cx + 1;
    }

    Y[0] = Y0;

    for (int j = 1; j < M; j++) {
        Y[j] = Y[j - 1] +
               ((long long)j * Ay + By) % Cy + 1;
    }

    long long low = X[0] + Y[0];
    long long high = X[N - 1] + Y[M - 1];

    while (low < high) {

        long long mid = low + (high - low) / 2;

        long long cnt = countPairs(X, Y, mid);

        if (cnt >= K)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}