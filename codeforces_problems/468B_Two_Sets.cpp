#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long a, b;
    if (!(cin >> n >> a >> b)) return 0;

    vector<long long> p(n + 1);
    map<long long, int> pos;

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    int node_a = n + 1;
    int node_b = n + 2;
    DSU dsu(n + 3);

    for (int i = 1; i <= n; i++) {
        long long x = p[i];
        if (pos.count(a - x)) {
            dsu.unite(i, pos[a - x]);
        } else {
            dsu.unite(i, node_b);
        }

        if (pos.count(b - x)) {
            dsu.unite(i, pos[b - x]);
        } else {
            dsu.unite(i, node_a);
        }
    }

    if (dsu.find(node_a) == dsu.find(node_b)) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        if (dsu.find(i) == dsu.find(node_a)) {
            cout << 0 << (i == n ? "" : " ");
        } else {
            cout << 1 << (i == n ? "" : " ");
        }
    }
    cout << "\n";

    return 0;
}
