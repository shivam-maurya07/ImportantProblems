#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e15;

vector<vector<long long>> seg;

vector<long long> merge(vector<long long> left,
                        vector<long long> right) {

    vector<long long> ans(4);

    // 0 -> sum
    // 1 -> prefix
    // 2 -> suffix
    // 3 -> best subarray

    ans[0] = left[0] + right[0];

    ans[1] = max(left[1],
                 left[0] + right[1]);

    ans[2] = max(right[2],
                 right[0] + left[2]);

    ans[3] = max({
        left[3],
        right[3],
        left[2] + right[1]
    });

    return ans;
}

void build(int idx, int low, int high,
           const vector<long long>& pnl) {

    if (low == high) {

        seg[idx] = {
            pnl[low],
            pnl[low],
            pnl[low],
            pnl[low]
        };

        return;
    }

    int mid = (low + high) / 2;

    build(2 * idx + 1, low, mid, pnl);
    build(2 * idx + 2, mid + 1, high, pnl);

    seg[idx] = merge(
        seg[2 * idx + 1],
        seg[2 * idx + 2]
    );
}

vector<long long> query(int idx, int l, int r,
                        int low, int high) {

    // No overlap
    if (low > r || high < l) {
        return {0, -INF, -INF, -INF};
    }

    // Complete overlap
    if (l <= low && high <= r) {
        return seg[idx];
    }

    int mid = (low + high) / 2;

    vector<long long> left =
        query(2 * idx + 1, l, r, low, mid);

    vector<long long> right =
        query(2 * idx + 2, l, r, mid + 1, high);

    if (left[3] == -INF) {
        return right;
    }

    if (right[3] == -INF) {
        return left;
    }

    return merge(left, right);
}

vector<long long> bestRangeProfit(
    int n,
    const vector<long long>& pnl,
    const vector<vector<int>>& queries) {

    // Convert pnl to 1-indexed
    vector<long long> arr(n + 1);

    for (int i = 1; i <= n; i++) {
        arr[i] = pnl[i - 1];
    }

    seg.resize(4 * n, vector<long long>(4));

    build(0, 1, n, arr);

    vector<long long> ans;

    for (auto q : queries) {

        int x1 = q[0];
        int y1 = q[1];
        int x2 = q[2];
        int y2 = q[3];

        long long max_pl = -INF;

        // Case 1:
        // i in [x1, x2-1]
        // j in [y1+1, y2]
        if (x1 <= x2 - 1 && y1 + 1 <= y2) {

            long long current =
                query(0, x1, x2 - 1, 1, n)[2]
                +
                query(0, x2, y1, 1, n)[0]
                +
                query(0, y1 + 1, y2, 1, n)[1];

            max_pl = max(max_pl, current);
        }

        // Case 2:
        // i in [x1, x2-1]
        // j in [x2, y1]
        if (x1 <= x2 - 1) {

            long long current =
                query(0, x1, x2 - 1, 1, n)[2]
                +
                query(0, x2, y1, 1, n)[1];

            max_pl = max(max_pl, current);
        }

        // Case 3:
        // i in [x2, y1]
        // j in [y1+1, y2]
        if (y1 + 1 <= y2) {

            long long current =
                query(0, x2, y1, 1, n)[2]
                +
                query(0, y1 + 1, y2, 1, n)[1];

            max_pl = max(max_pl, current);
        }

        // Case 4:
        // Both i and j are inside [x2, y1]
        max_pl = max(
            max_pl,
            query(0, x2, y1, 1, n)[3]
        );

        ans.push_back(max_pl);
    }

    return ans;
}