#include <bits/stdc++.h>
using namespace std;

const long long INF = 2e18;
const int MAXN = 200005;

struct Node {
    long long sum;
    long long mn;
    long long lazy;
};

Node tree[4 * MAXN];
long long a[MAXN];

void push_up(int node) {
    tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
    tree[node].mn = min(tree[2 * node].mn, tree[2 * node + 1].mn);
}

void apply_lazy(int node, int l, int r, long long val) {
    tree[node].sum += val * (r - l + 1);
    tree[node].mn += val;
    tree[node].lazy += val;
}

void push_down(int node, int l, int r) {
    if (tree[node].lazy != 0) {
        int mid = (l + r) / 2;
        apply_lazy(2 * node, l, mid, tree[node].lazy);
        apply_lazy(2 * node + 1, mid + 1, r, tree[node].lazy);
        tree[node].lazy = 0;
    }
}

void build(int node, int l, int r) {
    tree[node].lazy = 0;
    if (l == r) {
        tree[node].sum = a[l];
        tree[node].mn = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node, l, mid);
    build(2 * node + 1, mid + 1, r);
    push_up(node);
}

void update_add(int node, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        apply_lazy(node, l, r, val);
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update_add(2 * node, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        update_add(2 * node + 1, mid + 1, r, ql, qr, val);
    }
    push_up(node);
}

long long query_min(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node].mn;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    long long res = INF;
    if (ql <= mid) {
        res = min(res, query_min(2 * node, l, mid, ql, qr));
    }
    if (qr > mid) {
        res = min(res, query_min(2 * node + 1, mid + 1, r, ql, qr));
    }
    return res;
}

long long query_sum(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    long long res = 0;
    if (ql <= mid) {
        res += query_sum(2 * node, l, mid, ql, qr);
    }
    if (qr > mid) {
        res += query_sum(2 * node + 1, mid + 1, r, ql, qr);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("haybales.in", "r")) {
        freopen("haybales.in", "r", stdin);
        freopen("haybales.out", "w", stdout);
    }

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n);

    while (q--) {
        char type;
        cin >> type;
        if (type == 'M') {
            int l, r;
            cin >> l >> r;
            cout << query_min(1, 1, n, l, r) << "\n";
        } else if (type == 'P') {
            int l, r;
            long long c;
            cin >> l >> r >> c;
            update_add(1, 1, n, l, r, c);
        } else if (type == 'S') {
            int l, r;
            cin >> l >> r;
            cout << query_sum(1, 1, n, l, r) << "\n";
        }
    }

    return 0;
}
