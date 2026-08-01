// Summary to Never Forget:
// Unvisited? Paint it red, and explore it!
// Already Visited? Ask: "Did I just walk from here?"
// If Yes (neighbor == parent): Ignore it, just looking backwards.
// If No (neighbor != parent): CYCLE DETECTED!
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
        l[v].push_back(u);
    }
bool isCycleUndirBFS(int src, vector<bool> &vis){
queue<pair<int,int>> q;
q.push({src,-1});
vis[src] = true;

while(!q.empty()){
    int node = q.front().first;
    int parent = q.front().second;
    q.pop();

    for(auto i : l[node]){
        if(!vis[i]){
            vis[i]=true;
            q.push({i,node});
        }else if(i != parent){
return true;
        }
    }
}
return false;
}

bool isCycle(){
    vector<bool> v(V,false);

    for(int i=0;i<V;i++){
        if(!v[i]){
            if(isCycleUndirBFS(i,v)){

                return true;
            }
        }
    }
    return false;
}
};

int main() {    
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    cout<<g.isCycle()<<endl;
}