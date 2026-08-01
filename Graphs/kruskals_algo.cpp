#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Edge{
public:
int u,v,wt;
     Edge(int u, int v, int wt){
        this->u = u;
        this->v = v;
        this->wt = wt;
     }
     bool operator<(const Edge &other) const {
        return this->wt < other.wt;
     }
};

class Graph{
    public:
    int V;
    vector<Edge> edges;
    vector<int> par, rnk;

    Graph(int V){
        this->V = V;

        for(int i=0;i<V;i++){
            par.push_back(i);
            rnk.push_back(0);
        }
    }
    
    void addEdge(int u, int v, int wt){
        edges.push_back(Edge(u,v,wt));
    }
    
    int find(int i){
        if(par[i]==i){return i;}
        return par[i] = find(par[i]);
    }

    void unionByRank(int i,int j){
        int parA=find(i);
        int parB=find(j);

        if(parA==parB) return;

        if(rnk[parA]<rnk[parB]){
           par[parA]=parB;
        }
        else if(rnk[parA]>rnk[parB]){
            par[parB]=parA;
        }
        else{
            par[parB]=parA;
            rnk[parA]++;
        }
    }
    void kruskal(){
    sort(edges.begin(), edges.end());
    int mstCost = 0;

    for(int i=0;i<edges.size();i++){
        Edge e = edges[i];

        int parU = find(e.u); 
        int parV = find(e.v); 

        if(parU != parV){
            unionByRank(e.u,e.v);
            mstCost+=e.wt;
        }
    }
    cout<<"MST COST:"<<mstCost<<endl;
}
};



int main(){
    Graph g(4);

    g.addEdge(0,1,10);
    g.addEdge(0,2,6);
    g.addEdge(0,3,5);
    g.addEdge(1,3,15);
    g.addEdge(2,3,4);

    g.kruskal();
}