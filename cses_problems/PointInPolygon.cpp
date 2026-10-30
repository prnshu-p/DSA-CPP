#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

int orient(Point a, Point b, Point c) {
    long long val = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

bool on_segment(Point p, Point a, Point b) {
    return orient(a, b, p) == 0 &&
           p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Point> poly(n);
    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }

    while (m--) {
        Point p;
        cin >> p.x >> p.y;

        bool on_bound = false;
        int inside_count = 0;

        for (int i = 0; i < n; i++) {
            Point a = poly[i];
            Point b = poly[(i + 1) % n];

            if (on_segment(p, a, b)) {
                on_bound = true;
                break;
            }

            if (a.y > b.y) swap(a, b);

            if (p.y > a.y && p.y <= b.y) {
                if (orient(a, b, p) > 0) {
                    inside_count ^= 1;
                }
            }
        }

        if (on_bound) {
            cout << "BOUNDARY\n";
        } else if (inside_count) {
            cout << "INSIDE\n";
        } else {
            cout << "OUTSIDE\n";
        }
    }

    return 0;
}
