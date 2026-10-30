#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
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

    long long double_area = 0;
    long long b = 0;

    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        double_area += (p[i].x * p[next_i].y - p[next_i].x * p[i].y);
        long long dx = llabs(p[next_i].x - p[i].x);
        long long dy = llabs(p[next_i].y - p[i].y);
        b += gcd(dx, dy);
    }

    double_area = llabs(double_area);
    long long inside = (double_area - b + 2) / 2;

    cout << inside << " " << b << "\n";
    return 0;
}
