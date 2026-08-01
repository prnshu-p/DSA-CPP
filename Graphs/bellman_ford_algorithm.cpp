// shortest path from src to all vertices for weighted graph with negative weights
#include <bits/stdc++.h>
#include <queue>
using namespace std;

class Edge {
    public:
    int v,wt;

    Edge(int v, int wt){
        this->v = v;       
        this->wt = wt;       
    }
};

void bellman_ford(int src, vector<vector<Edge>> &g, int V){
    vector<int> dist(V,INT_MAX);
    dist[src] = 0;

    for(int i=0;i<V-1;i++){
        for(int u=0;u<V;u++){
             
            for(Edge &e:g[u]){
                int v = e.v;
                int wt = e.wt;
                if(dist[u] != INT_MAX && dist[v] > dist[u] + wt){
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }

    for(auto i : dist)cout<<i<<" ";
}

int main() {    
    int V = 5;
    vector<vector<Edge>> g(V);

    g[0].push_back(Edge(1,2));
    g[0].push_back(Edge(2,4));

    g[1].push_back(Edge(2,-4));
    g[1].push_back(Edge(4,-1));

    g[2].push_back(Edge(3,2));
    
    g[3].push_back(Edge(4,4));

    bellman_ford(0,g,V);

}