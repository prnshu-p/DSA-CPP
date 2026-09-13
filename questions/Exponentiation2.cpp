#include <iostream>

using namespace std;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        while (n--) {
            long long a, b, c;
            cin >> a >> b >> c;
            
            long long actual_exp = power(b, c, 1000000006);
            
            cout << power(a, actual_exp, 1000000007) << "\n";
        }
    }
    return 0;
}