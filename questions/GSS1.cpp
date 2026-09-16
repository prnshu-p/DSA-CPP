#include <iostream>
#include <algorithm>

using namespace std;

// Using long long for total immunity to hidden constraints
struct Node {
    long long total;
    long long pref;
    long long suf;
    long long best;
};

const int MAXN = 50005;
Node tree[4 * MAXN];
long long arr[MAXN];

Node merge(Node L, Node R) {
    Node res;
    res.total = L.total + R.total;
    res.pref = max(L.pref, L.total + R.pref);
    res.suf = max(R.suf, R.total + L.suf);
    
    // Nested max() to ensure compilation on older SPOJ servers
    res.best = max(max(L.best, R.best), L.suf + R.pref);
    
    return res;
}

// The Test 9 Savior: No 0s allowed. Negatives stay negative.
Node make_node(long long val) {
    Node res;
    res.total = val;
    res.pref = val;
    res.suf = val;
    res.best = val;
    return res;
}

void build(int node, int left, int right) {
    if (left == right) {
        tree[node] = make_node(arr[left]);
        return;
    }
    int mid = (left + right) / 2;
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

// The Split Query: Mathematically impossible to fetch an out-of-bounds Null Node
Node query(int node, int left, int right, int q_left, int q_right) {
    if (q_left <= left && right <= q_right) {
        return tree[node];
    }
    
    int mid = (left + right) / 2;
    
    if (q_right <= mid) {
        return query(2 * node, left, mid, q_left, q_right);
    }
    else if (q_left > mid) {
        return query(2 * node + 1, mid + 1, right, q_left, q_right);
    }
    else {
        Node L = query(2 * node, left, mid, q_left, q_right);
        Node R = query(2 * node + 1, mid + 1, right, q_left, q_right);
        return merge(L, R);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n);

    int q;
    if (!(cin >> q)) return 0;

    while (q--) {
        int a, b;
        cin >> a >> b;
        
        if (a > b) swap(a, b);
        
        Node res = query(1, 1, n, a, b);
        cout << res.best << "\n";
    }
    
    return 0;
}