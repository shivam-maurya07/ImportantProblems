#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long cross(vector<int>& o, vector<int>& a, vector<int>& b) {
        return 1LL * (a[0] - o[0]) * (b[1] - o[1])
             - 1LL * (a[1] - o[1]) * (b[0] - o[0]);
    }

    vector<vector<int>> convexHull(vector<vector<int>>& points) {
        int n = points.size();

        if (n <= 1) return points;

        sort(points.begin(), points.end());

        vector<vector<int>> lower, upper;

        // Lower hull
        for (auto& p : points) {
            while (lower.size() >= 2 &&
                   cross(lower[lower.size() - 2], lower.back(), p) < 0) {
                lower.pop_back();
            }
            lower.push_back(p);
        }

        // Upper hull
        for (int i = n - 1; i >= 0; i--) {
            auto& p = points[i];

            while (upper.size() >= 2 &&
                   cross(upper[upper.size() - 2], upper.back(), p) > 0) {
                upper.pop_back();
            }
            upper.push_back(p);
        }

        // Remove duplicate endpoints
        lower.pop_back();
        upper.pop_back();

        lower.insert(lower.end(), upper.begin(), upper.end());

        // Remove duplicate points while preserving cyclic order
        vector<vector<int>> hull;
        set<vector<int>> seen;

        for (auto p : lower) {
            if (seen.find(p) == seen.end()) {
                hull.push_back(p);
                seen.insert(p);
            }
        }

        return hull;
    }

    double totalArea(vector<vector<int>>& points, double r) {
        vector<vector<int>> hull = convexHull(points);
        int n = hull.size();

        if (n == 1) {
            return M_PI * r * r;
        }

        double area2 = 0.0;
        double perimeter = 0.0;

        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;

            double x1 = hull[i][0];
            double y1 = hull[i][1];
            double x2 = hull[j][0];
            double y2 = hull[j][1];

            // Shoelace formula
            area2 += x1 * y2 - y1 * x2;

            // Distance between consecutive hull points
            double dx = x2 - x1;
            double dy = y2 - y1;

            perimeter += sqrt(dx * dx + dy * dy);
        }

        double hullArea = abs(area2) / 2.0;

        // Area enclosed by the rubber band around the circles
        return hullArea + r * perimeter + M_PI * r * r;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> points = {
        {0, 0},
        {4, 0},
        {4, 4},
        {0, 4},
        {2, 2}
    };

    double r = 1.0;

    cout << fixed << setprecision(2);
    cout << sol.totalArea(points, r) << '\n';

    return 0;
}