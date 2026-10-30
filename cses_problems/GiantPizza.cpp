#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj, adj_rev;
vector<bool> vis;
vector<int> order, comp;

void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int c) {
    comp[u] = c;
    for (int v : adj_rev[u]) {
        if (comp[v] == 0) dfs2(v, c);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    int total_nodes = 2 * m + 2;
    adj.resize(total_nodes);
    adj_rev.resize(total_nodes);
    vis.assign(total_nodes, false);
    comp.assign(total_nodes, 0);

    auto get_node = [](char sign, int x) {
        return (sign == '+') ? (2 * x) : (2 * x + 1);
    };

    auto neg_node = [](int u) {
        return u ^ 1;
    };

    for (int i = 0; i < n; i++) {
        char s1, s2;
        int x1, x2;
        cin >> s1 >> x1 >> s2 >> x2;

        int u = get_node(s1, x1);
        int v = get_node(s2, x2);

        adj[neg_node(u)].push_back(v);
        adj[neg_node(v)].push_back(u);

        adj_rev[v].push_back(neg_node(u));
        adj_rev[u].push_back(neg_node(v));
    }

    for (int i = 2; i <= 2 * m + 1; i++) {
        if (!vis[i]) dfs1(i);
    }

    int num_comp = 0;
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (comp[u] == 0) {
            num_comp++;
            dfs2(u, num_comp);
        }
    }

    vector<char> ans(m + 1);
    for (int i = 1; i <= m; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        ans[i] = (comp[2 * i] < comp[2 * i + 1]) ? '+' : '-';
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << (i == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}
