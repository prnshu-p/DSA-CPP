#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9; 
const int MAXN = 200005;

int p[MAXN];
int tree_L[4 * MAXN]; 
int tree_R[4 * MAXN];

void build(int node, int start, int end) {
    if (start == end) {
        tree_L[node] = p[start] - start;
        tree_R[node] = p[start] + start;
        return;
    }
    
    int mid = (start + end) / 2;
    build(2 * node, start, mid);   
    build(2 * node + 1, mid + 1, end);  
    
    tree_L[node] = min(tree_L[2 * node], tree_L[2 * node + 1]);
    tree_R[node] = min(tree_R[2 * node], tree_R[2 * node + 1]);
}

void update(int node, int start, int end, int idx, int new_price) {
    if (start == end) {
        tree_L[node] = new_price - start;
        tree_R[node] = new_price + start;
        return;
    }
    
    int mid = (start + end) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx, new_price);
    } else {
        update(2 * node + 1, mid + 1, end, idx, new_price);
    }
    
    tree_L[node] = min(tree_L[2 * node], tree_L[2 * node + 1]);
    tree_R[node] = min(tree_R[2 * node], tree_R[2 * node + 1]);
}

int query_L(int node, int start, int end, int L, int R) {
    if (R < start || end < L) return INF; 
    if (L <= start && end <= R) return tree_L[node]; 
    
    int mid = (start + end) / 2;
    int left_ans = query_L(2 * node, start, mid, L, R);
    int right_ans = query_L(2 * node + 1, mid + 1, end, L, R);
    return min(left_ans, right_ans);
}

int query_R(int node, int start, int end, int L, int R) {
    if (R < start || end < L) return INF; 
    if (L <= start && end <= R) return tree_R[node]; 
    
    int mid = (start + end) / 2;
    int left_ans = query_R(2 * node, start, mid, L, R);
    int right_ans = query_R(2 * node + 1, mid + 1, end, L, R);
    return min(left_ans, right_ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, x;
            cin >> k >> x;
            update(1, 1, n, k, x);
        } 
        else if (type == 2) {
            int k;
            cin >> k;

            int min_left_base = query_L(1, 1, n, 1, k);
            int cost_left = min_left_base + k;

            int min_right_base = query_R(1, 1, n, k, n);
            int cost_right = min_right_base - k; 

            cout << min(cost_left, cost_right) << "\n";
        }
    }

    return 0;
}