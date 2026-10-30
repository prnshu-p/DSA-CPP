#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

long long mod_inv(long long n) {
    return power(n, MOD - 2);
}

long long nCr(long long n, int r) {
    if (n < r || r < 0) return 0;
    long long num = 1, den = 1;
    for (int i = 0; i < r; i++) {
        num = (num * ((n - i) % MOD)) % MOD;
        den = (den * (i + 1)) % MOD;
    }
    return (num * mod_inv(den)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long s;
    if (!(cin >> n >> s)) return 0;

    vector<long long> f(n);
    for (int i = 0; i < n; i++) cin >> f[i];

    long long ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        long long cur_s = s;
        int bits = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                cur_s -= (f[i] + 1);
                bits++;
            }
        }
        if (cur_s < 0) continue;

        long long ways = nCr(cur_s + n - 1, n - 1);
        if (bits % 2 == 1) {
            ans = (ans - ways + MOD) % MOD;
        } else {
            ans = (ans + ways) % MOD;
        }
    }

    cout << ans << "\n";
    return 0;
}
