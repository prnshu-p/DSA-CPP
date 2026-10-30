#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

bool compare_x(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

struct CompareY {
    bool operator()(const Point& a, const Point& b) const {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    }
};

long long dist_sq(Point a, Point b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(p.begin(), p.end(), compare_x);

    set<Point, CompareY> active_set;
    long long d = dist_sq(p[0], p[1]);
    active_set.insert(p[0]);
    active_set.insert(p[1]);

    int left = 0;
    for (int i = 2; i < n; i++) {
        while (left < i) {
            long long dx = p[i].x - p[left].x;
            if (dx * dx >= d) {
                active_set.erase(p[left]);
                left++;
            } else {
                break;
            }
        }

        long long d_sqrt = ceil(sqrt((double)d));
        Point low = {-2000000000LL, p[i].y - d_sqrt};
        Point high = {2000000000LL, p[i].y + d_sqrt};

        auto it_start = active_set.lower_bound(low);
        auto it_end = active_set.upper_bound(high);

        for (auto it = it_start; it != it_end; it++) {
            d = min(d, dist_sq(p[i], *it));
        }

        active_set.insert(p[i]);
    }

    cout << d << "\n";
    return 0;
}
