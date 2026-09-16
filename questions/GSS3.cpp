#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    long long total;
    long long pref;
    long long suf;
    long long best;
};

const int MAXN = 50005;
Node tree[4 * MAXN];
long long arr[MAXN];

// The God-Level Merge
Node merge(Node L, Node R) {
    Node res;
    res.total = L.total + R.total;
    res.pref = max(L.pref, L.total + R.pref);
    res.suf = max(R.suf, R.total + L.suf);
    res.best = max(max(L.best, R.best), L.suf + R.pref);
    return res;
}

// Converts a raw number into a 4-field Segment Tree Node
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

// THE UPGRADE: O(log N) Point Update
void update(int node, int left, int right, int idx, long long val) {
    // 1. We found the exact leaf. Overwrite it.
    if (left == right) {
        tree[node] = make_node(val);
        return;
    }
    
    // 2. Otherwise, figure out which child holds the index and walk down
    int mid = (left + right) / 2;
    if (idx <= mid) {
        update(2 * node, left, mid, idx, val);
    } else {
        update(2 * node + 1, mid + 1, right, idx, val);
    }
    
    // 3. The magic: Recalculate everything automatically on the way back up
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

// The Split Query (Test 9 Immune)
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
        int type;
        cin >> type;
        
        // Type 0: Update the array
        if (type == 0) {
            int idx;
            long long val;
            cin >> idx >> val;
            update(1, 1, n, idx, val);
        } 
        // Type 1: Query the maximum subarray sum
        else {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y); // SPOJ inverted query trap defense
            Node res = query(1, 1, n, x, y);
            cout << res.best << "\n";
        }
    }
    
    return 0;
}