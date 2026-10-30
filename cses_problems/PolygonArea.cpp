#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

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
    for (int i = 0; i < n; i++) {
        int next_i = (i + 1) % n;
        double_area += (p[i].x * p[next_i].y - p[next_i].x * p[i].y);
    }

    cout << llabs(double_area) << "\n";
    return 0;
}
