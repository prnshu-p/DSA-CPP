#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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

    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    if (p.size() <= 2) {
        cout << p.size() << "\n";
        for (auto pt : p) {
            cout << pt.x << " " << pt.y << "\n";
        }
        return 0;
    }

    vector<Point> lower, upper;
    for (int i = 0; i < (int)p.size(); i++) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), p[i]) < 0) {
            lower.pop_back();
        }
        lower.push_back(p[i]);
    }

    for (int i = (int)p.size() - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), p[i]) < 0) {
            upper.pop_back();
        }
        upper.push_back(p[i]);
    }

    lower.pop_back();
    upper.pop_back();

    vector<Point> hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());

    cout << hull.size() << "\n";
    for (auto pt : hull) {
        cout << pt.x << " " << pt.y << "\n";
    }

    return 0;
}
