#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long m, c;
    long long eval(long long x) const {
        return m * x + c;
    }
};

double intersect(const Line& l1, const Line& l2) {
    return (double)(l2.c - l1.c) / (l1.m - l2.m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<Line> hull;
    hull.push_back({b[0], 0});
    int ptr = 0;

    long long dp = 0;
    for (int i = 1; i < n; i++) {
        while (ptr + 1 < (int)hull.size() && hull[ptr].eval(a[i]) >= hull[ptr + 1].eval(a[i])) {
            ptr++;
        }
        dp = hull[ptr].eval(a[i]);

        Line cur = {b[i], dp};
        while (hull.size() >= 2 && intersect(hull[hull.size() - 2], cur) <= intersect(hull[hull.size() - 2], hull.back())) {
            hull.pop_back();
        }
        hull.push_back(cur);
        ptr = min(ptr, (int)hull.size() - 1);
    }

    cout << dp << "\n";
    return 0;
}
