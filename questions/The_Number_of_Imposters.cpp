#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSetUnion {
public:
    int n;
    vector<int> parent;
    vector<int> real_size;

    DisjointSetUnion(int original_n) {
        n = original_n * 2;
        parent.resize(n + 1);
        real_size.resize(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            if (i <= original_n) {
                real_size[i] = 1; 
            }
        }
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (real_size[root_i] < real_size[root_j]) {
                swap(root_i, root_j);
            }
            parent[root_j] = root_i;
            real_size[root_i] += real_size[root_j];
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    DisjointSetUnion dsu(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        string role;
        cin >> u >> v >> role;

        if (role[0] == 'c') { 
            dsu.unite(u, v);
            dsu.unite(u + n, v + n);
        } else { 
            dsu.unite(u, v + n);
            dsu.unite(u + n, v);
        }
    }

    int max_imposters = 0;
    vector<bool> root_visited(2 * n + 1, false);

    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == dsu.find(i + n)) {
            cout << -1 << "\n";
            return;
        }

        int root1 = dsu.find(i);      
        int root2 = dsu.find(i + n);   
        if (!root_visited[root1] && !root_visited[root2]) {
            max_imposters += max(dsu.real_size[root1], dsu.real_size[root2]);
            
            root_visited[root1] = true;
            root_visited[root2] = true;
        }
    }

    cout << max_imposters << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}