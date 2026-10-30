#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400005;
const int LOG = 20;

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n + 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j, int new_root) {
        parent[find(i)] = new_root;
        parent[find(j)] = new_root;
    }
};

int n, m, q;
vector<int> adj[MAXN];
int val[MAXN];
int up[MAXN][LOG], depth[MAXN];
int st[MAXN][LOG];
int lg[MAXN];

void dfs_krt(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_krt(v, u, d + 1);
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            u = up[u][j];
        }
    }
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    return up[u][0];
}

int query_st(int l, int r) {
    int j = lg[r - l + 1];
    return max(st[l][j], st[r - (1 << j) + 1][j]);
}

void solve() {
    cin >> n >> m >> q;

    int total_nodes = n;
    DSU dsu(2 * n + 5);

    for (int i = 1; i <= 2 * n + 5; i++) {
        adj[i].clear();
        val[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int ru = dsu.find(u);
        int rv = dsu.find(v);
        if (ru != rv) {
            total_nodes++;
            val[total_nodes] = i;
            adj[total_nodes].push_back(ru);
            adj[total_nodes].push_back(rv);
            adj[ru].push_back(total_nodes);
            adj[rv].push_back(total_nodes);
            dsu.unite(ru, rv, total_nodes);
        }
    }

    dfs_krt(total_nodes, total_nodes, 0);

    for (int i = 1; i < n; i++) {
        int lca = get_lca(i, i + 1);
        st[i][0] = val[lca];
    }

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i + (1 << j) - 1 < n; i++) {
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (l == r) {
            cout << 0 << " ";
        } else {
            cout << query_st(l, r - 1) << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lg[1] = 0;
    for (int i = 2; i < MAXN; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
