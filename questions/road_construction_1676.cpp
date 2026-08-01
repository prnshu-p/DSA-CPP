#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSetUnion {
public:
    int total_components;
    int largest_component;
    vector<int> parent, size;

    DisjointSetUnion(int n) {
        total_components = n; 
        largest_component = 1; 

        parent.resize(n);
        size.resize(n, 1); 

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void unionBySize(int i, int j) {
        int parA = find(i);
        int parB = find(j);

        if (parA == parB) return;

        if (size[parA] < size[parB]) {
            parent[parA] = parB;
            size[parB] += size[parA];
            largest_component = max(largest_component, size[parB]);
        } else {
            parent[parB] = parA;
            size[parA] += size[parB];
            largest_component = max(largest_component, size[parA]);
        }

        total_components--;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    DisjointSetUnion dsu(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        
        dsu.unionBySize(--a, --b);
        cout << dsu.total_components << " " << dsu.largest_component << "\n";
    }

    return 0;
}