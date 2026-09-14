#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
long long tree_sum[4 * MAXN];
long long lazy_add[4 * MAXN];
long long lazy_set[4 * MAXN];
long long arr[MAXN];

void apply_set(int node, int len, long long val) {
    tree_sum[node] = len * val;
    lazy_set[node] = val;
    lazy_add[node] = 0;
}

void apply_add(int node, int len, long long val) {
    if (lazy_set[node] != 0) {
        apply_set(node, len, lazy_set[node] + val);
    } else {
        tree_sum[node] += len * val;
        lazy_add[node] += val;
    }
}

void push_down(int node, int left, int right) {
    int mid = (left + right) / 2;
    int len_left = mid - left + 1;
    int len_right = right - mid;

    if (lazy_set[node] != 0) {
        apply_set(2 * node, len_left, lazy_set[node]);
        apply_set(2 * node + 1, len_right, lazy_set[node]);
        lazy_set[node] = 0;
    }
    
    if (lazy_add[node] != 0) {
        apply_add(2 * node, len_left, lazy_add[node]);
        apply_add(2 * node + 1, len_right, lazy_add[node]);
        lazy_add[node] = 0;
    }
}

void build(int node, int left, int right) {
    lazy_add[node] = lazy_set[node] = 0;
    if (left == right) {
        tree_sum[node] = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);
    tree_sum[node] = tree_sum[2 * node] + tree_sum[2 * node + 1];
}

void update_range(int node, int left, int right, int q_left, int q_right, int type, long long val) {
    if (q_right < left || q_left > right) return;
    
    if (q_left <= left && right <= q_right) {
        int len = right - left + 1;
        if (type == 1) apply_add(node, len, val);
        else apply_set(node, len, val);
        return;
    }
    
    push_down(node, left, right);
    
    int mid = (left + right) / 2;
    update_range(2 * node, left, mid, q_left, q_right, type, val);
    update_range(2 * node + 1, mid + 1, right, q_left, q_right, type, val);
    
    tree_sum[node] = tree_sum[2 * node] + tree_sum[2 * node + 1];
}

long long query_range(int node, int left, int right, int q_left, int q_right) {
    if (q_right < left || q_left > right) return 0;
    
    if (q_left <= left && right <= q_right) {
        return tree_sum[node];
    }
    
    push_down(node, left, right);
    
    int mid = (left + right) / 2;
    return query_range(2 * node, left, mid, q_left, q_right) + 
           query_range(2 * node + 1, mid + 1, right, q_left, q_right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; i++) cin >> arr[i];

    build(1, 1, n);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1 || type == 2) {
            int a, b;
            long long x;
            cin >> a >> b >> x;
            update_range(1, 1, n, a, b, type, x);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query_range(1, 1, n, a, b) << "\n";
        }
    }
    return 0;
}