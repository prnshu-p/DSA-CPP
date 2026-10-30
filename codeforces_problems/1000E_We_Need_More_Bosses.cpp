#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> tin, low;
vector<bool> is_bridge;
int timer = 0;

void dfs_bridges(int u, int p) {
    tin[u] = low[u] = ++timer;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        int id = edge.second;
        if (id == p) continue;

        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_bridges(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                is_bridge[id] = true;
            }
        }
    }
}

vector<int> comp;
int comp_cnt = 0;

void dfs_comp(int u, int c) {
    comp[u] = c;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        int id = edge.second;
        if (is_bridge[id] || comp[v]) continue;
        dfs_comp(v, c);
    }
}

pair<int, int> bfs(int start, int total_comps, const vector<vector<int>>& tree_adj) {
    vector<int> dist(total_comps + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthest_node = start;
    int max_d = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] > max_d) {
            max_d = dist[u];
            farthest_node = u;
        }

        for (int v : tree_adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    return {farthest_node, max_d};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    is_bridge.assign(m, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    dfs_bridges(1, -1);

    comp.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!comp[i]) {
            comp_cnt++;
            dfs_comp(i, comp_cnt);
        }
    }

    vector<vector<int>> tree_adj(comp_cnt + 1);
    for (int u = 1; u <= n; u++) {
        for (auto& edge : adj[u]) {
            int v = edge.first;
            if (comp[u] != comp[v]) {
                tree_adj[comp[u]].push_back(comp[v]);
            }
        }
    }

    auto p1 = bfs(1, comp_cnt, tree_adj);
    auto p2 = bfs(p1.first, comp_cnt, tree_adj);

    cout << p2.second << "\n";
    return 0;
}
