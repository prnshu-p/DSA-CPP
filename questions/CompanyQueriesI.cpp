#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

int up[MAXN][LOG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int v = 2; v <= n; v++) {
        cin >> up[v][0];
    }

    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            int halfway = up[v][j - 1];
            up[v][j] = up[halfway][j - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        int node, k;
        cin >> node >> k;

        for (int j = 0; j < LOG; j++) {
            if (k & (1 << j)) {        
                node = up[node][j];    
            }
        }

        if (node == 0) {
            cout << -1 << "\n";
        } else {
            cout << node << "\n";
        }
    }

    return 0;
}