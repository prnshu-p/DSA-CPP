#include <bits/stdc++.h>
using namespace std;

vector<long long> tree;

void build(int node, int start, int end, const vector<int>& h) {
    if (start == end) {
        tree[node] = h[start];
        return;
    }
    int mid = (start + end) / 2;
    int left_idx = 2 * node;
    int right_idx = 2 * node + 1;

    build(left_idx, start, mid, h);
    build(right_idx, mid + 1, end, h);
    
    tree[node] = max(tree[left_idx], tree[right_idx]);
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] -= val;
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
    
    tree[node] = max(tree[left_idx], tree[right_idx]);
}

int query(int node, int start, int end, long long val) {
    if (tree[node] < val) {
        return 0; 
    }
    
    // If we hit a leaf and it has enough capacity, this is our hotel
    if (start == end) {
        return start; 
    }

    int mid = (start + end) / 2;
    int left_idx = 2 * node;
    int right_idx = 2 * node + 1;

    // Prioritize the left side to get the smallest index. 
    if (tree[left_idx] >= val) {
        return query(left_idx, start, mid, val);
    } else {
        return query(right_idx, mid + 1, end, val);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    tree.resize(4 * n + 1);
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    build(1, 1, n, h);

    for (int i = 1; i <= m; i++) {
        long long rooms_needed;
        cin >> rooms_needed;
        
        int hotel_idx = query(1, 1, n, rooms_needed);
        
        cout << hotel_idx << " ";
        
        if (hotel_idx > 0) {
            update(1, 1, n, hotel_idx, rooms_needed);
        }
    }
    
    return 0;
}