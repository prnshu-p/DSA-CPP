#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 18;
const int INF = 1e9;
const int B = 320;

int n, m;
vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN];
int min_dist[MAXN];
bool is_red[MAXN];
vector<int> buffer;

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

int get_dist(int u, int v) {
    int l = get_lca(u, v);
    return depth[u] + depth[v] - 2 * depth[l];
}

void rebuild_bfs() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (is_red[i]) {
            min_dist[i] = 0;
            q.push(i);
        } else {
            min_dist[i] = INF;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (min_dist[v] > min_dist[u] + 1) {
                min_dist[v] = min_dist[u] + 1;
                q.push(v);
            }
        }
    }
    buffer.clear();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_lca(1, 1, 0);

    is_red[1] = true;
    rebuild_bfs();

    while (m--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            is_red[v] = true;
            buffer.push_back(v);
            if ((int)buffer.size() >= B) {
                rebuild_bfs();
            }
        } else {
            int ans = min_dist[v];
            for (int r : buffer) {
                ans = min(ans, get_dist(v, r));
            }
            cout << ans << "\n";
        }
    }

    return 0;
}
