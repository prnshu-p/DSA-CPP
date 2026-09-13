#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> order;
    queue<int> q;
    vector<int> parent(n + 1, 0);

    q.push(1);
    order.push_back(1);
    parent[1] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                q.push(v);
                order.push_back(v);
            }
        }
    }

    vector<long long> size(n + 1, 1);
    vector<long long> ans(n + 1, 0);
    
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v != parent[u]) {
                size[u] += size[v];
                ans[u] += ans[v] + size[v]; 
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v != parent[u]) {
                long long winners = size[v];
                long long losers = n - size[v];
                ans[v] = ans[u] - winners + losers;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}