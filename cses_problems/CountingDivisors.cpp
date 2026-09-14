#include <iostream>
#include <vector>

using namespace std;

const int MAXX = 1000000;
int divisors[MAXX + 1]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for (int i = 1; i <= MAXX; i++) {
        for (int j = i; j <= MAXX; j += i) {
            divisors[j]++;
        }
    }

    int n;
    if (cin >> n) {
        while (n--) {
            int x;
            cin >> x;

            cout << divisors[x] << "\n";
        }
    }
    return 0;
}