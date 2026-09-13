#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

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

    reverse(order.begin(), order.end());

    vector<long long> dp(n + 1, 1);
    
    for (int u : order) {
         for (int v : adj[u]) {
            if (v != parent[u]) {
                dp[u] = (dp[u] * (dp[v] + 1)) % m;
            }
        }
    }
    reverse(order.begin(), order.end());
    vector<long long> out(n + 1, 1); 

    for (int u : order) {
        vector<int> children;
        for (int v : adj[u]) {
            if (v != parent[u]) children.push_back(v);
        }

        int k = children.size();
        
        vector<long long> pref(k, 1), suff(k, 1);

        long long current_product = 1;
        for (int i = 0; i < k; i++) {
            pref[i] = current_product;
            current_product = (current_product * (dp[children[i]] + 1)) % m;
        }

        current_product = 1;
        for (int i = k - 1; i >= 0; i--) {
            suff[i] = current_product; 
            current_product = (current_product * (dp[children[i]] + 1)) % m;
        }

        for (int i = 0; i < k; i++) {
            int v = children[i];
            
            long long siblings = (pref[i] * suff[i]) % m;
            
            long long boss_contribution = (out[u] * siblings) % m;
            
            out[v] = (boss_contribution + 1) % m; 
        }
    }

    for (int i = 1; i <= n; i++) {
        long long final_ans = (dp[i] * out[i]) % m;
        cout << final_ans << "\n";
    }

    return 0;
}