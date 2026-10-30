#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int n, k;
vector<long long> pref;
vector<long long> dp_prev, dp_curr;

long long cost(int i, int j) {
    long long sum = pref[j] - pref[i];
    return sum * sum;
}

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<long long, int> best = {INF, -1};

    for (int p = optl; p <= min(mid - 1, optr); p++) {
        long long cur = dp_prev[p] + cost(p, mid);
        if (cur < best.first) {
            best = {cur, p};
        }
    }

    dp_curr[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> k)) return 0;

    pref.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    dp_prev.assign(n + 1, INF);
    dp_curr.assign(n + 1, INF);

    dp_prev[0] = 0;

    for (int g = 1; g <= k; g++) {
        compute(1, n, 0, n - 1);
        dp_prev = dp_curr;
    }

    cout << dp_prev[n] << "\n";
    return 0;
}
