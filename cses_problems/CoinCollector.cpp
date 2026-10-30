#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> coins;
vector<vector<int>> adj, adj_rev;
vector<bool> vis;
vector<int> order, comp;
vector<long long> scc_coins;
vector<vector<int>> scc_adj;
vector<long long> dp;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    scc_coins[c] += coins[u];
    for (int v : adj_rev[u]) {
        if (comp[v] == 0) {
            dfs2(v, c);
        }
    }
}

long long get_max_coins(int u) {
    if (dp[u] != -1) return dp[u];
    long long mx = 0;
    for (int v : scc_adj[u]) {
        mx = max(mx, get_max_coins(v));
    }
    return dp[u] = scc_coins[u] + mx;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    coins.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> coins[i];

    adj.resize(n + 1);
    adj_rev.resize(n + 1);
    vis.assign(n + 1, false);
    comp.assign(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs1(i);
    }

    int num_scc = 0;
    scc_coins.assign(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == 0) {
            num_scc++;
            dfs2(u, num_scc);
        }
    }

    scc_adj.resize(num_scc + 1);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (comp[u] != comp[v]) {
                scc_adj[comp[u]].push_back(comp[v]);
            }
        }
    }

    dp.assign(num_scc + 1, -1);
    long long ans = 0;
    for (int i = 1; i <= num_scc; i++) {
        ans = max(ans, get_max_coins(i));
    }

    cout << ans << "\n";
    return 0;
}
