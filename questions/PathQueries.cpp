#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
long long values[MAXN];

long long flat_array[2 * MAXN]; 
int tin[MAXN], tout[MAXN];
int timer = 0;

void walk(int person, int parent) {
    timer++;
    tin[person] = timer;
    flat_array[timer] = values[person]; 
    
    for (int worker : adj[person]) {
        if (worker != parent) {
            walk(worker, person); 
        }
    }
    
    timer++;
    tout[person] = timer;
    flat_array[timer] = -values[person]; 
}

long long tree[8 * MAXN]; 

void build(int node, int lo, int hi) {
    if (lo == hi) {
        tree[node] = flat_array[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    build(2 * node, lo, mid);
    build(2 * node + 1, mid + 1, hi);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int lo, int hi, int idx, long long val) {
    if (lo == hi) {
        tree[node] = val;
        return;
    }
    int mid = (lo + hi) / 2;
    if (idx <= mid) update(2 * node, lo, mid, idx, val);
    else update(2 * node + 1, mid + 1, hi, idx, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

long long query(int node, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return 0LL; 
    if (l <= lo && hi <= r) return tree[node];
    
    int mid = (lo + hi) / 2;
    return query(2 * node, lo, mid, l, r) + query(2 * node + 1, mid + 1, hi, l, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> values[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    walk(1, 0);

    build(1, 1, 2 * n);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int s;
            long long x;
            cin >> s >> x;
            
            update(1, 1, 2 * n, tin[s], x);
            update(1, 1, 2 * n, tout[s], -x);
            values[s] = x;
        } 
        else if (type == 2) {
            int s;
            cin >> s;
            cout << query(1, 1, 2 * n, 1, tin[s]) << "\n";
        }
    }

    return 0;
}