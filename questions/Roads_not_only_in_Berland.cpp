#include <iostream>
#include <algorithm>
#include <vector>
#include <map> 
using namespace std; 

class DisjointSetUnion {
public:
    int n;
    vector<int> parent, size;
    vector<pair<int,int>> rp; 

    DisjointSetUnion(int n) {
        this->n = n;
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
        
        if (parA == parB) {
            rp.push_back({i,j});
            return;
        } 

        if (size[parA] < size[parB]) {
            parent[parA] = parB;
            size[parB] += size[parA];
        } else {
            parent[parB] = parA;
            size[parA] += size[parB];
        }
    } 

    void answer() {
        map<int,int> m; 
        
        for(int i = 0; i < n; i++) {
            m[find(i)]++; 
        }
        
        cout << m.size() - 1 << endl;
        
        auto it = m.begin();
        auto next_it = it;
        next_it++;
        
        int idx = 0;
        while (next_it != m.end()) {
            cout <<rp[idx].first+1  << " " << rp[idx].second + 1 << " " << (it->first) + 1 << " " << (next_it->first) + 1 << "\n";
            it++;
            next_it++;
            idx++;
        }
    }
}; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    DisjointSetUnion dsu(n);

    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        dsu.unionBySize(--a,--b);
    }

    dsu.answer();
    
    return 0;
}