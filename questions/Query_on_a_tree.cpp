#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 10005;
const int INF = 1e9 + 7;

struct Edge {
    int to;
    int weight;
    int id;
};

vector<Edge> adj[MAXN];
int parent_node[MAXN], depth[MAXN], subtree_size[MAXN];
int heavy_child[MAXN], head[MAXN], pos[MAXN];
int edge_to_node[MAXN]; 

int node_to_edge_weight[MAXN]; 
int flattened_val[MAXN];

int current_pos = 1;
int global_n;

int tree_max[2 * MAXN];

void build() {
    for (int i = 1; i <= global_n; i++) {
        tree_max[global_n + i - 1] = flattened_val[i];
    }
    for (int i = global_n - 1; i > 0; --i) {
        tree_max[i] = max(tree_max[i << 1], tree_max[i << 1 | 1]);
    }
}

void update(int p, int new_val) {
    for (tree_max[p += global_n - 1] = new_val; p > 1; p >>= 1) {
        tree_max[p >> 1] = max(tree_max[p], tree_max[p ^ 1]);
    }
}

int query_seg(int l, int r) {
    int res = -INF; 
    for (l += global_n - 1, r += global_n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = max(res, tree_max[l++]);
        if (r & 1) res = max(res, tree_max[--r]);
    }
    return res;
}

void dfs1(int u, int p, int d) {
    parent_node[u] = p;
    depth[u] = d;
    subtree_size[u] = 1;
    heavy_child[u] = -1;
    
    int max_sub = 0;
    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v != p) {
            edge_to_node[edge.id] = v; 
            node_to_edge_weight[v] = edge.weight; 
            
            dfs1(v, u, d + 1);
            
            subtree_size[u] += subtree_size[v];
            if (subtree_size[v] > max_sub) {
                max_sub = subtree_size[v];
                heavy_child[u] = v;
            }
        }
    }
}

void dfs2(int u, int p, int current_head) {
    head[u] = current_head;
    pos[u] = current_pos;
    
    flattened_val[current_pos] = node_to_edge_weight[u];
    current_pos++;
    
    if (heavy_child[u] != -1) {
        dfs2(heavy_child[u], u, current_head);
    }
    
    for (auto& edge : adj[u]) {
        int v = edge.to;
        if (v != p && v != heavy_child[u]) {
            dfs2(v, u, v);
        }
    }
}

int query_path(int a, int b) {
    if (a == b) return 0;
    
    int res = -INF; 
        while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]]) swap(a, b);
        res = max(res, query_seg(pos[head[a]], pos[a]));
        a = parent_node[head[a]];
    }
    if (depth[a] > depth[b]) swap(a, b);
    
    if (pos[a] + 1 <= pos[b]) {
        res = max(res, query_seg(pos[a] + 1, pos[b]));
    }
    return res;
}

void solve() {
    cin >> global_n;
    
    for (int i = 1; i <= global_n; i++) {
        adj[i].clear();
    }
    current_pos = 1;
    
    for (int i = 1; i < global_n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w, i});
        adj[v].push_back({u, w, i});
    }
    
    node_to_edge_weight[1] = 0; 
    
    dfs1(1, 0, 0);
    dfs2(1, 0, 1);
    build();
    
    string op;
    while (cin >> op && op[0] != 'D') {
        if (op[0] == 'C') { 
            int idx, new_weight;
            cin >> idx >> new_weight;
            int owner_node = edge_to_node[idx];
            update(pos[owner_node], new_weight);
        } else if (op[0] == 'Q') { 
            int a, b;
            cin >> a >> b;
            cout << query_path(a, b) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}