#include <bits/stdc++.h>
using namespace std;

vector<vector<long long>> seg;

vector<long long> mergeNode(vector<long long> left,
                            vector<long long> right) {

    vector<long long> res(4);

    // 0 -> sum
    // 1 -> prefix
    // 2 -> suffix
    // 3 -> best

    res[0] = left[0] + right[0];

    res[1] = max(left[1],
                 left[0] + right[1]);

    res[2] = max(right[2],
                 right[0] + left[2]);

    res[3] = max({
        left[3],
        right[3],
        left[2] + right[1]
    });

    return res;
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

    int mid = low + (high - low) / 2;

    build(2 * idx + 1, low, mid, pnl);
    build(2 * idx + 2, mid + 1, high, pnl);

    seg[idx] = mergeNode(
        seg[2 * idx + 1],
        seg[2 * idx + 2]
    );
}

vector<long long> query(int idx, int low, int high,
                        int l, int r) {

    // Complete overlap
    if (l <= low && high <= r)
        return seg[idx];

    // No overlap
    if (high < l || r < low)
        return {0, LLONG_MIN, LLONG_MIN, LLONG_MIN};

    int mid = low + (high - low) / 2;

    vector<long long> left =
        query(2 * idx + 1, low, mid, l, r);

    vector<long long> right =
        query(2 * idx + 2, mid + 1, high, l, r);

    if (left[1] == LLONG_MIN)
        return right;

    if (right[1] == LLONG_MIN)
        return left;

    return mergeNode(left, right);
}


vector<long long> bestRangeProfit(
    int n,
    const vector<long long>& pnl,
    const vector<pair<int, int>>& queries
) {

    seg.resize(4 * n, vector<long long>(4));

    build(0, 0, n - 1, pnl);

    vector<long long> ans;

    for (auto [l, r] : queries) {

        // 1-indexed queries
        l--;
        r--;

        vector<long long> res =
            query(0, 0, n - 1, l, r);

        ans.push_back(res[3]);
    }

    return ans;
}