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
     void dfs(int curr,vector<bool>&vis,stack<int> &s){
        vis[curr]=true;
        for(auto &v:l[curr]){
            if(!vis[v]) {
                dfs(v,vis,s);
            }
        }
        s.push(curr);  
    }
   void ts(){
    vector<bool> vis(V,false);
    stack<int> s;

    for(int i=0;i<V;i++){
        if(!vis[i]){
            dfs(i,vis,s);
        }
    }
    while(!s.empty()){
        cout<<s.top()<<" ";
        s.pop();
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

g.ts();
}