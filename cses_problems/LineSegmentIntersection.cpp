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
    return p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);
}

void solve() {
    Point a, b, c, d;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    int o1 = orient(a, b, c);
    int o2 = orient(a, b, d);
    int o3 = orient(c, d, a);
    int o4 = orient(c, d, b);

    if (o1 != o2 && o3 != o4) {
        cout << "YES\n";
        return;
    }

    if (o1 == 0 && on_segment(c, a, b)) { cout << "YES\n"; return; }
    if (o2 == 0 && on_segment(d, a, b)) { cout << "YES\n"; return; }
    if (o3 == 0 && on_segment(a, c, d)) { cout << "YES\n"; return; }
    if (o4 == 0 && on_segment(b, c, d)) { cout << "YES\n"; return; }

    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
