#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 20;

int up[MAXN][LOG];
int depth[MAXN];         
vector<int> adj[MAXN];    

// A lightning-fast DFS just to calculate everyone's depth
void dfs(int node, int current_depth) {
    depth[node] = current_depth;
    for (int child : adj[node]) {
        dfs(child, current_depth + 1);
    }
}

int get_lca(int a, int b) {
    // We always want 'a' to be the deeper worker. 
    // If 'a' is higher up, we just swap their name tags to make the code easier.
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

    for (int v = 2; v <= n; v++) {
        cin >> up[v][0];
        adj[up[v][0]].push_back(v);
    }

    dfs(1, 0);

    for (int j = 1; j < LOG; j++) {
        for (int v = 1; v <= n; v++) {
            int halfway = up[v][j - 1];
            up[v][j] = up[halfway][j - 1];
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        cout << get_lca(a, b) << "\n";
    }

    return 0;
}