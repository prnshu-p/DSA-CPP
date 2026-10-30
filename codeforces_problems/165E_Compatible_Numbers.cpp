#include <bits/stdc++.h>
using namespace std;

const int BITS = 22;
const int MAX_MASK = 1 << BITS;

int dp[MAX_MASK];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[a[i]] = a[i];
    }

    for (int b = 0; b < BITS; b++) {
        for (int mask = 0; mask < MAX_MASK; mask++) {
            if (mask & (1 << b)) {
                if (dp[mask ^ (1 << b)] != -1) {
                    dp[mask] = dp[mask ^ (1 << b)];
                }
            }
        }
    }

    int full_mask = MAX_MASK - 1;
    for (int i = 0; i < n; i++) {
        int comp = full_mask ^ a[i];
        cout << dp[comp] << (i + 1 == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
