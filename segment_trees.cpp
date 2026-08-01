#include <bits/stdc++.h>
using namespace std;

const int N = 200005; 
long long tree[4 * N]; // The Segment Tree
long long arr[N];      // The original 1-indexed array

void build(int node, int start, int end) {
    // Base Case: We hit a leaf (a single element)
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    
    // Recursive Step: Split the range
    int mid = (start + end) / 2;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    
    build(left_child, start, mid);         // Build left half
    build(right_child, mid + 1, end);      // Build right half
    
    // The Invariant: Merge the two children to update the current manager
    tree[node] = tree[left_child] + tree[right_child]; 
}

void update(int node, int start, int end, int idx, long long val) {
    // Base Case: We found the exact leaf to update
    if (start == end) {
        tree[node] = val;
        return;
    }
    
    // Find which child contains our target index
    int mid = (start + end) / 2;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    
    if (idx <= mid) {
        update(left_child, start, mid, idx, val);    // Go left
    } else {
        update(right_child, mid + 1, end, idx, val); // Go right
    }
    
    // CRITICAL: Re-merge on the way up so the ancestors know about the change!
    tree[node] = tree[left_child] + tree[right_child];
}

long long query(int node, int start, int end, int l, int r) {
    // Scenario 2: No overlap
    if (r < start || end < l) {
        return 0; // The identity value for addition.
    }
    
    // Scenario 1: Complete overlap
    if (l <= start && end <= r) {
        return tree[node]; // We don't recurse further! This is the speed secret.
    }
    
    // Scenario 3: Partial overlap (split and merge the answers)
    int mid = (start + end) / 2;
    long long left_ans = query(2 * node, start, mid, l, r);
    long long right_ans = query(2 * node + 1, mid + 1, end, l, r);
    
    return left_ans + right_ans;
}