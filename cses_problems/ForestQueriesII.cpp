#include <bits/stdc++.h>
using namespace std;

int n, q;
int bit[1005][1005];
char grid[1005][1005];

void update(int y, int x, int val) {
    for (int i = y; i <= n; i += i & -i) {
        for (int j = x; j <= n; j += j & -j) {
            bit[i][j] += val;
        }
    }
}

int query(int y, int x) {
    int sum = 0;
    for (int i = y; i > 0; i -= i & -i) {
        for (int j = x; j > 0; j -= j & -j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int query_rect(int y1, int x1, int y2, int x2) {
    return query(y2, x2) - query(y1 - 1, x2) - query(y2, x1 - 1) + query(y1 - 1, x1 - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '*') {
                update(i, j, 1);
            }
        }
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            if (grid[y][x] == '*') {
                update(y, x, -1);
                grid[y][x] = '.';
            } else {
                update(y, x, 1);
                grid[y][x] = '*';
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query_rect(y1, x1, y2, x2) << "\n";
        }
    }

    return 0;
}
