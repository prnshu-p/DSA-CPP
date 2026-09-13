#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> dp(1 << n, 0);

    dp[0] = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
        int man = __builtin_popcount(mask) - 1;

        for (int w = 0; w < n; w++) {
            if ((mask & (1 << w)) && a[man][w] == 1) {
                int prev_mask = mask - (1 << w);
                
                dp[mask] = (dp[mask] + dp[prev_mask]) % MOD;
            }
        }
    }

    cout << dp[(1 << n) - 1] << "\n";

    return 0;
}