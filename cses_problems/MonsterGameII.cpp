#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;
const int MAX_X = 1000000;

struct Line {
    long long m, c;
    long long eval(long long x) const {
        return m * x + c;
    }
};

Line tree[4 * (MAX_X + 5)];

void insert(int node, int l, int r, Line line) {
    int mid = (l + r) / 2;
    bool left = line.eval(l) < tree[node].eval(l);
    bool mid_better = line.eval(mid) < tree[node].eval(mid);

    if (mid_better) {
        swap(tree[node], line);
    }

    if (l == r) return;

    if (left != mid_better) {
        insert(2 * node, l, mid, line);
    } else {
        insert(2 * node + 1, mid + 1, r, line);
    }
}

long long query(int node, int l, int r, int x) {
    long long res = tree[node].eval(x);
    if (l == r) return res;

    int mid = (l + r) / 2;
    if (x <= mid) {
        return min(res, query(2 * node, l, mid, x));
    } else {
        return min(res, query(2 * node + 1, mid + 1, r, x));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> s(n), f(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> f[i];

    for (int i = 0; i < 4 * (MAX_X + 5); i++) {
        tree[i] = {0, INF};
    }

    insert(1, 0, MAX_X, {x, 0});

    long long dp = 0;
    for (int i = 0; i < n; i++) {
        dp = query(1, 0, MAX_X, s[i]);
        insert(1, 0, MAX_X, {f[i], dp});
    }

    cout << dp << "\n";
    return 0;
}
