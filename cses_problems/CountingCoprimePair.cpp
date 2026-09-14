#include <iostream>
#include <vector>

using namespace std;

const int MAXX = 1000000;

int mu[MAXX + 1];
int freq[MAXX + 1];
int multiples[MAXX + 1];
bool is_prime[MAXX + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 1; i <= MAXX; i++) {
        mu[i] = 1; 
        is_prime[i] = true;
    }
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p <= MAXX; p++) {
        if (is_prime[p]) {
            for (int i = p; i <= MAXX; i += p) {
                is_prime[i] = false;
                if ((i / p) % p == 0) {
                    mu[i] = 0;
                } else {
                    mu[i] *= -1;
                }
            }
        }
    }

    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    for (int i = 1; i <= MAXX; i++) {
        for (int curr = i; curr <= MAXX; curr += i) {
            multiples[i] += freq[curr];
        }
    }

    long long total_coprime_pairs = 0;
    for (int i = 1; i <= MAXX; i++) {
        if (mu[i] != 0 && multiples[i] > 1) {
            long long pairs = (long long)multiples[i] * (multiples[i] - 1) / 2;
            
            total_coprime_pairs += mu[i] * pairs;
        }
    }

    cout << total_coprime_pairs << "\n";

    return 0;
}