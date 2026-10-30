#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    long long cp = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    if (cp > 0) {
        cout << "LEFT\n";
    } else if (cp < 0) {
        cout << "RIGHT\n";
    } else {
        cout << "TOUCH\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
