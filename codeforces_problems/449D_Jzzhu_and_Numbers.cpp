#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int BITS = 20;
const int MAX_MASK = 1 << BITS;

int f[MAX_MASK];
int p2[MAX_MASK + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        f[x]++;
    }

    p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p2[i] = (p2[i - 1] * 2) % MOD;
    }

    for (int b = 0; b < BITS; b++) {
        for (int mask = MAX_MASK - 1; mask >= 0; mask--) {
            if (!(mask & (1 << b))) {
                f[mask] = (f[mask] + f[mask | (1 << b)]) % MOD;
            }
        }
    }

    long long ans = 0;
    for (int mask = 0; mask < MAX_MASK; mask++) {
        long long ways = (p2[f[mask]] - 1 + MOD) % MOD;
        if (__builtin_popcount(mask) % 2 == 1) {
            ans = (ans - ways + MOD) % MOD;
        } else {
            ans = (ans + ways) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
