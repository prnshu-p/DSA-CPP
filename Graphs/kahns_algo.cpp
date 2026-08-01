#include <bits/stdc++.h>
#include <queue>
using namespace std;

class Graph {
    int V;
    list<int>* l;

   public:
    Graph(int V) {
        this->V = V;
        l = new list<int>[V];
    }
    
    void addEdge(int u, int v) {
        l[u].push_back(v);
    }

    void kahns() {
    queue<int> q;
    vector<int> indeg(V,0);

    for(int i=0;i<V;i++){
        for(auto v : l[i]){
            indeg[v]++;
        }
    }

    for(int i=0;i<V;i++){
        if(indeg[i]==0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int curr = q.front();
        cout<<curr<<" ";
        q.pop();

    for(int v : l[curr]){
        indeg[v]--;
        if(indeg[v]==0){
            q.push(v);
        }
    }
    }
    cout<<endl;
    }
};

int main() {    
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

g.kahns();
}