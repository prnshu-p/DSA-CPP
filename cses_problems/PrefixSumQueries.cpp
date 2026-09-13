#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

struct Node {
    long long sum, pref;
};

Node identity_node() { 
    return {0LL, 0LL}; // Return BOTH sum and pref
}

Node single(long long v) { 
    return {v, max(0LL, v)}; 
}

Node merge(Node L, Node R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    return res;
}

// ==========================================
// TREE MACHINERY
// ==========================================
Node tree[4 * MAXN];
long long arr[MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = single(arr[start]);
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = single(val);
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid)
        update(2 * node, start, mid, idx, val);
    else
        update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return identity_node();
    if (l <= start && end <= r) return tree[node];

    int mid = (start + end) / 2;
    return merge(query(2 * node, start, mid, l, r),
                 query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, u;
            cin >> k >> u;
            update(1, 1, n, k, u);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query(1, 1, n, a, b).pref << "\n";
        }
    }

    return 0;
}