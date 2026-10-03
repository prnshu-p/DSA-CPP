#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 8000000;

int lc[MAX_NODES];       
int rc[MAX_NODES];       
long long sum[MAX_NODES];
int node_cnt = 0;        

int build(int L, int R, const vector<int>& arr) {
    int id = ++node_cnt;
    if (L == R) {
        sum[id] = arr[L];
        return id;
    }
    int mid = L + (R - L) / 2;
    lc[id] = build(L, mid, arr);
    rc[id] = build(mid + 1, R, arr);
    sum[id] = sum[lc[id]] + sum[rc[id]];
    return id;
}

int update(int prev_id, int L, int R, int idx, long long val) {
    int id = ++node_cnt;
    
    
    lc[id] = lc[prev_id];
    rc[id] = rc[prev_id];
    sum[id] = sum[prev_id];
    
    
    if (L == R) {
        sum[id] = val;
        return id;
    }
    
    int mid = L + (R - L) / 2;
    
    if (idx <= mid) {
        lc[id] = update(lc[prev_id], L, mid, idx, val);
    } else {
        rc[id] = update(rc[prev_id], mid + 1, R, idx, val);
    }
    
    sum[id] = sum[lc[id]] + sum[rc[id]];
    return id;
}

long long query(int id, int L, int R, int ql, int qr) {
    if (ql <= L && R <= qr) {
        return sum[id];
    }
    int mid = L + (R - L) / 2;
    long long ans = 0;
    if (ql <= mid) ans += query(lc[id], L, mid, ql, qr);
    if (qr > mid)  ans += query(rc[id], mid + 1, R, ql, qr);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    if (!(cin >> n >> q)) return 0;
    
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    
    vector<int> roots;
    roots.push_back(0);
    roots.push_back(build(1, n, arr));
    
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, a;
            long long x;
            cin >> k >> a >> x;
            
            roots[k] = update(roots[k], 1, n, a, x);
        } else if (type == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            cout << query(roots[k], 1, n, a, b) << "\n";
        } else if (type == 3) {
            int k;
            cin >> k;
            
            roots.push_back(roots[k]);
        }
    }
    
    return 0;
}