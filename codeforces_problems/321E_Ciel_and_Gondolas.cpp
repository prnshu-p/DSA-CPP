#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, k;
int pref[4005][4005];
int dp_prev[4005], dp_curr[4005];

inline int get_cost(int i, int j) {
    return (pref[j][j] - pref[i - 1][j] - pref[j][i - 1] + pref[i - 1][i - 1]) / 2;
}

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<int, int> best = {INF, -1};

    for (int p = optl; p <= min(mid - 1, optr); p++) {
        int cur = dp_prev[p] + get_cost(p + 1, mid);
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

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + val;
        }
    }

    for (int i = 1; i <= n; i++) {
        dp_prev[i] = get_cost(1, i);
    }
    dp_prev[0] = 0;

    for (int g = 2; g <= k; g++) {
        compute(1, n, 0, n - 1);
        for (int i = 1; i <= n; i++) {
            dp_prev[i] = dp_curr[i];
        }
    }

    cout << dp_prev[n] << "\n";
    return 0;
}
