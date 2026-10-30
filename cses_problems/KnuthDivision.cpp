#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int n;
long long pref[5005];
long long dp[5005][5005];
short opt[5005][5005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
        opt[i][i] = i;
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = INF;
            int start_k = opt[i][j - 1];
            int end_k = opt[i + 1][j];
            long long range_sum = pref[j] - pref[i - 1];

            for (int m = start_k; m <= end_k; m++) {
                long long cur = dp[i][m] + dp[m + 1][j] + range_sum;
                if (cur < dp[i][j]) {
                    dp[i][j] = cur;
                    opt[i][j] = m;
                }
            }
        }
    }

    cout << dp[1][n] << "\n";
    return 0;
}
