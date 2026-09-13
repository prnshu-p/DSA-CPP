#include <bits/stdc++.h>
using namespace std;

vector<long long> tree;

void build(int node, int start, int end, const vector<int>& arr) {
    if (start == end) {
        tree[node] = arr[start];
        return; 
    }
    int mid = (start + end) / 2;
    int left_idx = 2 * node;
    int right_idx = 2 * node + 1;
    
    build(left_idx, start, mid, arr);
    build(right_idx, mid + 1, end, arr);

    tree[node] = min(tree[left_idx], tree[right_idx]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;
    int left_idx = 2 * node;
    int right_idx = 2 * node + 1;

    if (idx <= mid) {
        update(left_idx, start, mid, idx, val); 
    } else {
        update(right_idx, mid + 1, end, idx, val);  
    }

    tree[node] = min(tree[left_idx], tree[right_idx]);
}

long long query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return LLONG_MAX;
    }

    if (l <= start && end <= r) {
        return tree[node]; 
    }

    int mid = (start + end) / 2;
    long long left_ans = query(2 * node, start, mid, l, r);
    long long right_ans = query(2 * node + 1, mid + 1, end, l, r);

    return min(left_ans, right_ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    tree.resize(4 * n + 1);

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, 1, n, arr);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            long long u;
            cin >> k >> u;
            update(1, 1, n, k, u);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query(1, 1, n, a, b) << "\n";
        }
    }
    
    return 0;
}