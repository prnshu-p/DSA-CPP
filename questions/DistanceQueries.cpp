#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

int up[MAXN][LOG];
int depth[MAXN];          
vector<int> adj[MAXN];

void dfs(int node, int parent, int current_depth) {
    depth[node] = current_depth;
    up[node][0] = parent; 
    
    for (int child : adj[node]) {
        if (child != parent) { 
            dfs(child, node, current_depth + 1);
        }
    }
}

int get_lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    int diff = depth[a] - depth[b];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            a = up[a][j];
        }
    }

    if (a == b) return a;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0, 0);

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            int halfway = up[i][j - 1];
            up[i][j] = up[halfway][j - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        
        int lca = get_lca(a, b);
        int distance = depth[a] + depth[b] - (2 * depth[lca]);
        
        cout << distance << "\n";
    }

    return 0;
}