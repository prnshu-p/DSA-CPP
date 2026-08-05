#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

// 1. WHAT DATA DOES A NODE HOLD?
struct Node {
    // TODO: Add your fields here (e.g., long long sum, best, etc.)
};

// 2. THE GHOST CHILD (Neutral Element)
Node identity() { 
    // TODO: Return the neutral state. 
    // (e.g., 0 for sum, 0 for XOR, infinity for minimum)
    return {}; 
}

// 3. THE LEAF NODE (Single Element)
Node single(long long v) { 
    // TODO: Build and return a node from a single array value 'v'.
    return {}; 
}

// 4. THE GLUER (Combine Left and Right)
Node merge(Node L, Node R) { 
    Node res;
    // TODO: Write the logic to combine L and R into res
    
    return res;
}

// ==========================================
// TREE MACHINERY (You never need to touch this)
// ==========================================
Node tree[4 * MAXN];
long long a[MAXN];
int n, q;

void build(int node, int start, int end) {
    if (start == end) { 
        tree[node] = single(a[start]); 
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
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else            update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return identity();
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    // IMPORTANT: Left child must always be queried first for directional merges
    return merge(query(2 * node, start, mid, l, r),
                 query(2 * node + 1, mid + 1, end, l, r));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Read n, q, array
    // build(1, 1, n);
    // Process queries
    
    return 0;
}