#include <iostream>
#include <cstring>

using namespace std;

const int N = 1e5 + 5;
long long b1[N];
long long b2[N];
int n; 

void add(long long* b, int i, long long v) {
    for (; i <= n; i += (i & -i)) {
        b[i] += v;
    }
}

void rangeAdd(int l, int r, long long v) {
    add(b1, l, v);
    add(b1, r + 1, -v);
    add(b2, l, v * l);
    add(b2, r + 1, -v * (r + 1));
}

long long get(long long* b, int i) {
    long long total = 0;
    for (; i > 0; i -= (i & -i)) {
        total += b[i];
    }
    return total;
}

long long prefixSum(long long x) {
    return (x + 1) * get(b1, x) - get(b2, x);
}

long long rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int c;
        cin >> n >> c;

        memset(b1, 0, sizeof(b1));
        memset(b2, 0, sizeof(b2));

        for (int i = 0; i < c; i++) {
            int type, p, q;
            cin >> type >> p >> q;
            
            if (type == 0) {
                long long v;
                cin >> v;
                rangeAdd(p, q, v);
            } else {
                cout << rangeSum(p, q) << "\n";
            }
        }
    }
    return 0;
}