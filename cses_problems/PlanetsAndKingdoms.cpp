#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, adj_rev;
vector<bool> visited;
vector<int> order, comp;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : adj_rev[u]) {
        if (comp[v] == 0) {
            dfs2(v, c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    adj_rev.resize(n + 1);
    visited.assign(n + 1, false);
    comp.assign(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    int num_comp = 0;
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == 0) {
            num_comp++;
            dfs2(u, num_comp);
        }
    }

    cout << num_comp << "\n";
    for (int i = 1; i <= n; i++) {
        cout << comp[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}
