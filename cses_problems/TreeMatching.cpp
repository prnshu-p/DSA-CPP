#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int parent[MAXN];
int dp[MAXN][2];

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

    for (int u : order) {
        
        int sum_solo = 0;
        
        for (int v : adj[u]) {
            if (v != parent[u]) {
                sum_solo += max(dp[v][0], dp[v][1]);
            }
        }
        
        dp[u][0] = sum_solo;

        dp[u][1] = 0; 
        for (int v : adj[u]) {
            if (v != parent[u]) {
                int test_score = sum_solo - max(dp[v][0], dp[v][1]) + dp[v][0] + 1;
                
                dp[u][1] = max(dp[u][1], test_score);
            }
        }
    }

    cout << max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}