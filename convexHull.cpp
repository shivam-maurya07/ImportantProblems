

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

ll cross(pair<ll, ll> O, pair<ll, ll> A, pair<ll, ll> B) {
    return (A.first - O.first) * (B.second - O.second)
         - (A.second - O.second) * (B.first - O.first);
}

double enclosedArea(int n, int k, const vector<int>& xs,
                    const vector<int>& ys) {
    vector<pair<ll, ll>> p;

    for (int i = 0; i < n; i++) {
        p.push_back({xs[i], ys[i]});
    }

    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int m = p.size();
    vector<pair<ll, ll>> h;

    // Lower hull
    for (auto pt : p) {
        while (h.size() >= 2 &&
               cross(h[h.size() - 2], h.back(), pt) <= 0) {
            h.pop_back();
        }
        h.push_back(pt);
    }

    // Upper hull
    int lower = h.size();

    for (int i = m - 2; i >= 0; i--) {
        while ((int)h.size() > lower &&
               cross(h[h.size() - 2], h.back(), p[i]) <= 0) {
            h.pop_back();
        }
        h.push_back(p[i]);
    }

    if (h.size() > 1) {
        h.pop_back();
    }

    ld area = 0, perimeter = 0;
    int sz = h.size();

    if (sz >= 3) {
        for (int i = 0; i < sz; i++) {
            int j = (i + 1) % sz;

            area += (ld)h[i].first * h[j].second
                  - (ld)h[i].second * h[j].first;

            perimeter += hypotl(
                (ld)(h[j].first - h[i].first),
                (ld)(h[j].second - h[i].second)
            );
        }

        area = fabsl(area) / 2.0L;
    } 
    else if (sz == 2) {
        perimeter = 2.0L * hypotl(
            (ld)(h[1].first - h[0].first),
            (ld)(h[1].second - h[0].second)
        );
    }

    ld ans = area + perimeter * k + acosl(-1.0L) * k * k;

    return (double)ans;
}

//////////////////////////////////////////////////////////------ans2-----------------------------
// #include <bits/stdc++.h>
// using namespace std;

// using ld = long double;

// struct Point {
//     long long x, y;

//     bool operator<(const Point& other) const {
//         if (x != other.x) return x < other.x;
//         return y < other.y;
//     }

//     bool operator==(const Point& other) const {
//         return x == other.x && y == other.y;
//     }
// };

// ld cross(Point a, Point b, Point c) {
//     return (ld)(b.x - a.x) * (c.y - a.y)
//          - (ld)(b.y - a.y) * (c.x - a.x);
// }

// ld dist(Point a, Point b) {
//     return hypotl((ld)a.x - b.x, (ld)a.y - b.y);
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     ld R;
//     int N;
//     long long D;
//     cin >> R >> N >> D;

//     vector<Point> pts(N);
//     for (int i = 0; i < N; i++) {
//         cin >> pts[i].x >> pts[i].y;
//     }

//     sort(pts.begin(), pts.end());
//     pts.erase(unique(pts.begin(), pts.end()), pts.end());

//     int n = pts.size();
//     vector<Point> hull;

//     // Lower hull
//     for (auto p : pts) {
//         while (hull.size() >= 2 &&
//                cross(hull[hull.size() - 2],
//                      hull.back(), p) <= 0) {
//             hull.pop_back();
//         }
//         hull.push_back(p);
//     }

//     // Upper hull
//     int lowerSize = hull.size();

//     for (int i = n - 2; i >= 0; i--) {
//         while ((int)hull.size() > lowerSize &&
//                cross(hull[hull.size() - 2],
//                      hull.back(), pts[i]) <= 0) {
//             hull.pop_back();
//         }
//         hull.push_back(pts[i]);
//     }

//     if (hull.size() > 1) {
//         hull.pop_back();
//     }

//     // Calculate hull area and perimeter
//     ld area = 0;
//     ld perimeter = 0;
//     int m = hull.size();

//     for (int i = 0; i < m; i++) {
//         Point a = hull[i];
//         Point b = hull[(i + 1) % m];

//         perimeter += dist(a, b);
//         area += (ld)a.x * b.y - (ld)a.y * b.x;
//     }

//     area = fabsl(area) / 2.0L;

//     // Expanded convex hull area
//     ld answer = area + R * perimeter
//                       + acosl(-1.0L) * R * R;

//     cout << fixed << setprecision(10) << answer << '\n';

//     return 0;
// }
