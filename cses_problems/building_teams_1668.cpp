#include <iostream>
#include <vector>

using namespace std;

struct ParityDSU {
    vector<int> parent;
    vector<int> parity; 

    ParityDSU(int n) {
        parent.resize(n);
        parity.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        
        int p = parent[v];
        parent[v] = find_set(parent[v]); 
        parity[v] ^= parity[p]; 
        
        return parent[v];
    }

    bool union_sets(int a, int b) {
        int root_a = find_set(a);
        int root_b = find_set(b);

        if (root_a == root_b) {
            if (parity[a] == parity[b])
                return false; 
        } else {
            parent[root_a] = root_b;
            parity[root_a] = parity[a] ^ parity[b] ^ 1;
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    ParityDSU dsu(n);

    bool possible = true;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v; 
        
        if (!dsu.union_sets(u, v)) {
            possible = false;
        }
    }

    if (!possible) {
        cout << "IMPOSSIBLE\n";
    } else {
        for (int i = 0; i < n; i++) {
            dsu.find_set(i);
            
            cout << dsu.parity[i] + 1 << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}