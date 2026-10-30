#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

vector<int> adj[MAXN];
int val[MAXN];
int parent_node[MAXN], depth[MAXN], subtree_size[MAXN];
int heavy_child[MAXN], head[MAXN], pos[MAXN];
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
    int res = 0;
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
    for (int v : adj[u]) {
        if (v != p) {
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
    flattened_val[current_pos] = val[u];
    current_pos++;
    
    if (heavy_child[u] != -1) {
        dfs2(heavy_child[u], u, current_head);
    }
    
    for (int v : adj[u]) {
        if (v != p && v != heavy_child[u]) {
            dfs2(v, u, v);
        }
    }
}

int query_path(int a, int b) {
    int res = 0;
    while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]]) swap(a, b);
        res = max(res, query_seg(pos[head[a]], pos[a]));
        a = parent_node[head[a]];
    }
    if (depth[a] > depth[b]) swap(a, b);
    res = max(res, query_seg(pos[a], pos[b]));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (!(cin >> global_n >> q)) return 0;

    for (int i = 1; i <= global_n; i++) cin >> val[i];

    for (int i = 0; i < global_n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1, 0, 0);
    dfs2(1, 0, 1);
    
    build();

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int s, x;
            cin >> s >> x;
            update(pos[s], x);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query_path(a, b) << " ";
        }
    }
    cout << "\n";
    return 0;
}