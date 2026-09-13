#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int start_node, int n, const vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    
    q.push(start_node);
    dist[start_node] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) { 
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    // Start anywhere (Node 1). The furthest node found is one end of the diameter.
    vector<int> dist_from_1 = bfs(1, n, adj);
    int nodeA = 1;
    for (int i = 1; i <= n; i++) {
        if (dist_from_1[i] > dist_from_1[nodeA]) {
            nodeA = i;
        }
    }

    // Start from Node A. The furthest node found is the other end of the diameter.
    vector<int> distA = bfs(nodeA, n, adj);
    int nodeB = 1;
    for (int i = 1; i <= n; i++) {
        if (distA[i] > distA[nodeB]) {
            nodeB = i;
        }
    }

    // Start from Node B to get distances from the other endpoint.
    vector<int> distB = bfs(nodeB, n, adj);

    // logic: the answer is just the max of the two distances.
    for (int i = 1; i <= n; i++) {
        cout << max(distA[i], distB[i]) << (i == n ? "" : " ");
    }
    cout << "\n";

    return 0;
}