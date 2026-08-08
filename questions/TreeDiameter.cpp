#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int parent[MAXN];

int dp[MAXN]; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> order;
    queue<int> q;

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

    int global_record = 0; 

    for (int u : order) {
        for (int v : adj[u]) {
            if (v != parent[u]) {
                global_record = max(global_record, dp[u] + dp[v] + 1);
                
                dp[u] = max(dp[u], dp[v] + 1);
            }
        }
    }

    cout << global_record << "\n";

    return 0;
}