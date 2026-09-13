#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
long long values[MAXN];
long long flat_array[MAXN];
int tin[MAXN], tout[MAXN];
int badge_counter = 0;

void walk(int person, int parent) {
    tin[person] = ++badge_counter; 
    flat_array[badge_counter] = values[person]; 
    
    for (int worker : adj[person]) {
        if (worker != parent) { 
            walk(worker, person); 
        }
    }
    
    tout[person] = badge_counter; 
}

long long tree[4 * MAXN];

void build(int node, int start, int end) {
 
   if (start == end) {
        tree[node] = flat_array[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int node, int start, int end, int idx, long long val) {
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid) update(2 * node, start, mid, idx, val);
    else update(2 * node + 1, mid + 1, end, idx, val);
    tree[node] = tree[2 * node] + tree[2 * node + 1]; 
}

long long query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) return 0LL; 
    if (l <= start && end <= r) return tree[node];
    
    int mid = (start + end) / 2;
    return query(2 * node, start, mid, l, r) + query(2 * node + 1, mid + 1, end, l, r);
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

    build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int s;
            long long x;
            cin >> s >> x;
            update(1, 1, n, tin[s], x);
        } 
        else if (type == 2) {
            int s;
            cin >> s;
            cout << query(1, 1, n, tin[s], tout[s]) << "\n";
        }
    }

    return 0;
}