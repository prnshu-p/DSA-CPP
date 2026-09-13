#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

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

    // Reverse the clipboard so workers do their math before the bosses
    reverse(order.begin(), order.end());

    // Everyone starts with 1 valid way to paint their own empty room
    vector<long long> dp_white(n + 1, 1);
    vector<long long> dp_black(n + 1, 1);

    for (int u : order) {
        for (int v : adj[u]) {
            if (v != parent[u]) { 
                
                // Worker v can be White OR Black. (We add them up, then multiply into the Boss's total)
                long long worker_total = (dp_white[v] + dp_black[v]) % MOD;
                dp_white[u] = (dp_white[u] * worker_total) % MOD;
                
                // Worker v MUST be White. (We just take the White ways and multiply)
                dp_black[u] = (dp_black[u] * dp_white[v]) % MOD;
            }
        }
    }

    long long total_ways = (dp_white[1] + dp_black[1]) % MOD;
    
    cout << total_ways << "\n";

    return 0;
}