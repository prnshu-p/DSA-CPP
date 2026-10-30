#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int LOG = 17;

int n, k;
vector<int> adj[MAXN];
int up[MAXN][LOG], depth[MAXN];
int val[MAXN];
int max_flow = 0;

void dfs_lca(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_lca(v, u, d + 1);
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

void dfs_flow(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs_flow(v, u);
            val[u] += val[v];
        }
    }
    max_flow = max(max_flow, val[u]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (fopen("maxflow.in", "r")) {
        freopen("maxflow.in", "r", stdin);
        freopen("maxflow.out", "w", stdout);
    }

    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_lca(1, 0, 0);

    while (k--) {
        int u, v;
        cin >> u >> v;
        int lca = get_lca(u, v);
        val[u]++;
        val[v]++;
        val[lca]--;
        if (up[lca][0] != 0) {
            val[up[lca][0]]--;
        }
    }

    dfs_flow(1, 0);

    cout << max_flow << "\n";
    return 0;
}
