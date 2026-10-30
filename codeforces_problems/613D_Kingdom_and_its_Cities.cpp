#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 18;

int n, q;
vector<int> adj[MAXN];
int up[MAXN][LOG];
int depth[MAXN], tin[MAXN], tout[MAXN];
int timer = 0;

bool is_marked[MAXN];
vector<int> virt_adj[MAXN];
int ans = 0;

void dfs_tree(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    tin[u] = ++timer;

    for (int j = 1; j < LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }

    for (int v : adj[u]) {
        if (v != p) {
            dfs_tree(v, u, d + 1);
        }
    }
    tout[u] = timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int get_lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int j = LOG - 1; j >= 0; j--) {
        if (!is_ancestor(up[u][j], v)) {
            u = up[u][j];
        }
    }
    return up[u][0];
}

bool dfs_dp(int u) {
    int cnt = 0;
    for (int v : virt_adj[u]) {
        if (dfs_dp(v)) {
            cnt++;
        }
    }

    if (is_marked[u]) {
        ans += cnt;
        return true;
    } else {
        if (cnt > 1) {
            ans++;
            return false;
        } else if (cnt == 1) {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_tree(1, 1, 0);

    if (!(cin >> q)) return 0;

    while (q--) {
        int k;
        cin >> k;
        vector<int> nodes(k);
        for (int i = 0; i < k; i++) {
            cin >> nodes[i];
            is_marked[nodes[i]] = true;
        }

        bool bad = false;
        for (int u : nodes) {
            if (u != 1 && is_marked[up[u][0]]) {
                bad = true;
                break;
            }
        }

        if (bad) {
            cout << -1 << "\n";
            for (int u : nodes) is_marked[u] = false;
            continue;
        }

        sort(nodes.begin(), nodes.end(), [](int a, int b) {
            return tin[a] < tin[b];
        });

        vector<int> all_v = nodes;
        for (int i = 0; i < k - 1; i++) {
            all_v.push_back(get_lca(nodes[i], nodes[i + 1]));
        }

        sort(all_v.begin(), all_v.end(), [](int a, int b) {
            return tin[a] < tin[b];
        });
        all_v.erase(unique(all_v.begin(), all_v.end()), all_v.end());

        stack<int> st;
        for (int u : all_v) {
            while (!st.empty() && !is_ancestor(st.top(), u)) {
                st.pop();
            }
            if (!st.empty()) {
                virt_adj[st.top()].push_back(u);
            }
            st.push(u);
        }

        ans = 0;
        dfs_dp(all_v[0]);

        cout << ans << "\n";

        for (int u : all_v) {
            virt_adj[u].clear();
        }
        for (int u : nodes) {
            is_marked[u] = false;
        }
    }

    return 0;
}
