#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> tin, low;
vector<bool> visited_edge;
int timer = 0;
bool has_bridge = false;
vector<pair<int, int>> oriented_edges;

void dfs(int u, int p) {
    tin[u] = low[u] = ++timer;

    for (auto& edge : adj[u]) {
        int v = edge.first;
        int id = edge.second;

        if (visited_edge[id]) continue;
        visited_edge[id] = true;

        oriented_edges.push_back({u, v});

        if (!tin[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                has_bridge = true;
            }
        } else {
            low[u] = min(low[u], tin[v]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    tin.assign(n + 1, 0);
    low.assign(n + 1, 0);
    visited_edge.assign(m, false);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    dfs(1, 0);

    if (has_bridge || (int)oriented_edges.size() != m) {
        cout << 0 << "\n";
    } else {
        for (auto& edge : oriented_edges) {
            cout << edge.first << " " << edge.second << "\n";
        }
    }

    return 0;
}
