#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

int n;
vector<Edge> adj[MAXN];
int sz[MAXN], heavy[MAXN], depth[MAXN], mask_val[MAXN];
int in_time[MAXN], out_time[MAXN], node_at[MAXN];
int timer = 0;
int ans[MAXN];
int max_depth_mask[(1 << 22) + 5];

void dfs_sz(int u, int d, int m) {
    depth[u] = d;
    mask_val[u] = m;
    sz[u] = 1;
    heavy[u] = -1;
    in_time[u] = ++timer;
    node_at[timer] = u;

    int max_sub = 0;
    for (auto& edge : adj[u]) {
        int v = edge.to;
        dfs_sz(v, d + 1, m ^ edge.weight);
        sz[u] += sz[v];
        if (sz[v] > max_sub) {
            max_sub = sz[v];
            heavy[u] = v;
        }
    }
    out_time[u] = timer;
}

void dfs_sack(int u, bool keep) {
    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v != heavy[u]) {
            dfs_sack(v, false);
            ans[u] = max(ans[u], ans[v]);
        }
    }

    if (heavy[u] != -1) {
        dfs_sack(heavy[u], true);
        ans[u] = max(ans[u], ans[heavy[u]]);
    }

    if (max_depth_mask[mask_val[u]] != -INF) {
        ans[u] = max(ans[u], max_depth_mask[mask_val[u]] - depth[u]);
    }
    for (int bit = 0; bit < 22; bit++) {
        int target = mask_val[u] ^ (1 << bit);
        if (max_depth_mask[target] != -INF) {
            ans[u] = max(ans[u], max_depth_mask[target] - depth[u]);
        }
    }
    max_depth_mask[mask_val[u]] = max(max_depth_mask[mask_val[u]], depth[u]);

    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v != heavy[u]) {
            for (int t = in_time[v]; t <= out_time[v]; t++) {
                int node = node_at[t];
                if (max_depth_mask[mask_val[node]] != -INF) {
                    ans[u] = max(ans[u], max_depth_mask[mask_val[node]] + depth[node] - 2 * depth[u]);
                }
                for (int bit = 0; bit < 22; bit++) {
                    int target = mask_val[node] ^ (1 << bit);
                    if (max_depth_mask[target] != -INF) {
                        ans[u] = max(ans[u], max_depth_mask[target] + depth[node] - 2 * depth[u]);
                    }
                }
            }
            for (int t = in_time[v]; t <= out_time[v]; t++) {
                int node = node_at[t];
                max_depth_mask[mask_val[node]] = max(max_depth_mask[mask_val[node]], depth[node]);
            }
        }
    }

    if (!keep) {
        for (int t = in_time[u]; t <= out_time[u]; t++) {
            int node = node_at[t];
            max_depth_mask[mask_val[node]] = -INF;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 2; i <= n; i++) {
        int p;
        char c;
        cin >> p >> c;
        adj[p].push_back({i, 1 << (c - 'a')});
    }

    dfs_sz(1, 0, 0);

    for (int i = 0; i < (1 << 22); i++) {
        max_depth_mask[i] = -INF;
    }

    dfs_sack(1, true);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
