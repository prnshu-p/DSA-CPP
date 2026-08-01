#include <iostream>
#include <vector>
using namespace std; 

class DisjointSetUnion {
public:
    int n;
    vector<int> parent, relation; 

    DisjointSetUnion(int n){
        this->n = n;
        parent.resize(n);
        relation.resize(n, 0); 
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        int root = find(parent[x]);
        relation[x] = relation[x] ^ relation[parent[x]];
        return parent[x] = root;
    }

    void addGang(int x, int y){
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            parent[rootX] = rootY;
            relation[rootX] = relation[x] ^ relation[y] ^ 1;
        }
    }

    void checkGang(int a, int b){
        int rootA = find(a);
        int rootB = find(b);
        
        if (rootA == rootB) { 
            if (relation[a] == relation[b]) {
                cout << "In the same gang.\n";
            } else {
                cout << "In different gangs.\n";
            }
        } else { 
            cout << "Not sure yet.\n";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        cin >> n >> m;
       
        DisjointSetUnion dsu(n);

        for (int i = 0; i < m; i++) {
            int a, b;
            string s;
            cin >> s >> a >> b;
            if (s == "D") {
                dsu.addGang(--a, --b);
            } else {
                dsu.checkGang(--a, --b);
            }
        }
    }
    return 0;
}