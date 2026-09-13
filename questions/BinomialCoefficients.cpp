#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int MAXN = 1000000;
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

    int n;
    if (cin >> n) {
        while (n--) {
            long long a, b; 
            cin >> a >> b;
            
            long long ans = fact[a];
            ans = (ans * modInverse(fact[b])) % MOD;
            ans = (ans * modInverse(fact[a - b])) % MOD;
            
            cout << ans << "\n";
        }
    }
    return 0;
}