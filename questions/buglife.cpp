#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion {
public:
    int n;
    vector<int> parent, sex;

    DisjointSetUnion(int n) {
        this->n = n;
        parent.resize(n);
        sex.resize(n, 0);
        for (int i = 0; i < n; i++) { 
            parent[i] = i; 
        }
    }

    int find(int i) {
        if (parent[i] == i) return i;
        int boss = find(parent[i]);
        sex[i] = sex[i] ^ sex[parent[i]];
        parent[i] = boss;
        return parent[i];
    }

    bool unite(int x, int y, int d) {
        int bx = find(x), by = find(y);
        if (bx == by) {
            return (sex[x] ^ sex[y]) == d; 
        }
        sex[by] = sex[x] ^ sex[y] ^ d;
        parent[by] = bx;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (!(cin >> t)) return 0;
    
    for (int tc = 1; tc <= t; tc++) {
        int n, m;
        cin >> n >> m;
        
        DisjointSetUnion dsu(n);
        bool suspicious = false;

        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            
            if (!suspicious) {
                bool res = dsu.unite(a, b, 1);
                if (!res) {
                    suspicious = true;
                }
            }
        }
    
        cout << "Scenario #" << tc << ":\n";
        if (suspicious) {
            cout << "Suspicious bugs found!\n";
        } else {
            cout << "No suspicious bugs found!\n";
        }
    }
    return 0;
}