#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, adj_rev;
vector<bool> vis;

void dfs(int u, const vector<vector<int>>& g) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v, g);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    adj_rev.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    vis.assign(n + 1, false);
    dfs(1, adj);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "NO\n";
            cout << 1 << " " << i << "\n";
            return 0;
        }
    }

    vis.assign(n + 1, false);
    dfs(1, adj_rev);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cout << "NO\n";
            cout << i << " " << 1 << "\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
