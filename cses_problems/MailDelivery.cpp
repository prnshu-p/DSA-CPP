#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<bool> used;
vector<int> path;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;

    adj.resize(n + 1);
    used.assign(m, false);

    vector<int> deg(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }

    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 != 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    stack<int> st;
    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        while (!adj[u].empty() && used[adj[u].back().second]) {
            adj[u].pop_back();
        }

        if (adj[u].empty()) {
            path.push_back(u);
            st.pop();
        } else {
            auto edge = adj[u].back();
            adj[u].pop_back();
            int v = edge.first;
            int id = edge.second;
            if (!used[id]) {
                used[id] = true;
                st.push(v);
            }
        }
    }

    if ((int)path.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i] << (i + 1 == (int)path.size() ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
