#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

struct Node {
    long long sum, pref,suf,best;
};

Node identity_node() { 
    return {0LL, 0LL,0LL,0LL}; // Return BOTH sum and pref
}

Node single(long long v) { 
    return {
        v,             
        max(0LL, v),    
        max(0LL, v),    
        max(0LL, v)     
    }; 
}
Node merge(Node L, Node R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suf = max(R.suf,  R.sum + L.suf);
    res.best = max({L.best, R.best, L.suf+R.pref});
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

Node query() {
    return tree[1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        
        int k, u;
        cin >> k >> u;
        update(1, 1, n, k, u);
        cout <<query().best << "\n";
        
    }

    return 0;
}