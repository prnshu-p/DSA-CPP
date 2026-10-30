#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_VAL = 1000005;
int freq[MAX_VAL];
int current_distinct = 0;
int BLOCK_SIZE;

int arr[30005];
int ans[200005];

struct Query {
    int l, r, id;
};
Query q[200005];

bool compareQueries(Query a, Query b) {
    int block_a = a.l / BLOCK_SIZE;
    int block_b = b.l / BLOCK_SIZE;
    
    if (block_a != block_b) {
        return block_a < block_b;
    }
    return a.r < b.r;
}

void add(int idx) {
    freq[arr[idx]]++;
    if (freq[arr[idx]] == 1) {
        current_distinct++;
    }
}

void remove(int idx) {
    freq[arr[idx]]--;
    if (freq[arr[idx]] == 0) {
        current_distinct--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    
    BLOCK_SIZE = sqrt(n);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }

    sort(q, q + m, compareQueries);

    int L = 1, R = 0;

    for (int i = 0; i < m; i++) {
        int target_L = q[i].l;
        int target_R = q[i].r;

        while (L > target_L) {
            L--;
            add(L);
        }
        while (R < target_R) {
            R++;
            add(R);
        }
        
        while (L < target_L) {
            remove(L);
            L++;
        }
        while (R > target_R) {
            remove(R);
            R--;
        }

       ans[q[i].id] = current_distinct;
    }

    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}