#include <iostream>

using namespace std;

const int MOD = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (cin >> n) {
        if (n == 1) {
            cout << 0 << "\n";
            return 0;
        }
        if (n == 2) {
            cout << 1 << "\n";
            return 0;
        }

        long long prev2 = 0;
        long long prev1 = 1;
        long long current = 0;

        for (long long i = 3; i <= n; i++) {
            current = (i - 1) * (prev1 + prev2) % MOD;
            
            prev2 = prev1;
            prev1 = current;
        }

        cout << current << "\n";
    }
    return 0;
}