#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int n, k;
vector<long long> c, prefC, prefIC;
vector<vector<long long>> cost_val;
vector<long long> dp_prev, dp_curr;

long long get_cost(int i, int j, int m) {
    long long left_part = (long long)m * (prefC[m] - prefC[i - 1]) - (prefIC[m] - prefIC[i - 1]);
    long long right_part = (prefIC[j] - prefIC[m]) - (long long)m * (prefC[j] - prefC[m]);
    return left_part + right_part;
}

void compute(int l, int r, int optl, int optr) {
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<long long, int> best = {INF, -1};

    for (int p = optl; p <= min(mid - 1, optr); p++) {
        long long cur = dp_prev[p] + cost_val[p + 1][mid];
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

    c.resize(n + 1);
    prefC.assign(n + 1, 0);
    prefIC.assign(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        prefC[i] = prefC[i - 1] + c[i];
        prefIC[i] = prefIC[i - 1] + (long long)i * c[i];
    }

    cost_val.assign(n + 2, vector<long long>(n + 2, 0));
    for (int i = 1; i <= n; i++) {
        int m = i;
        for (int j = i; j <= n; j++) {
            while (m < j && (prefC[m] - prefC[i - 1]) < (prefC[j] - prefC[m])) {
                m++;
            }
            cost_val[i][j] = get_cost(i, j, m);
        }
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
