#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 2000000; 
long long fact[MAXN + 1];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    long long n, m;
    if (cin >> n >> m) {
        long long top = m + n - 1;
        long long bottom = n - 1;
        
        long long ans = fact[top];
        ans = (ans * modInverse(fact[bottom])) % MOD;
        ans = (ans * modInverse(fact[top - bottom])) % MOD;
        
        cout << ans << "\n";
    }
    return 0;
}