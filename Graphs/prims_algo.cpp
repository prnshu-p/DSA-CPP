#include <bits/stdc++.h>
#include <queue>
using namespace std;

void prims(int V, vector<vector<pair<int,int>>> &g){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    vector<bool> inMST(V,false);
    int cost = 0;
    pq.push({0,0});

    while(!pq.empty()){
        int wt=pq.top().first,u=pq.top().second;
        pq.pop();

        if(!inMST[u]){
            inMST[u] = true;
            cost += wt;

            for(auto v : g[u]){
                if(!inMST[v.first]){
                    pq.push({v.second,v.first});
                }
            }
        }
    }
  cout<<cost;
    
}


int main() {    
    int V = 5;
    vector<vector<pair<int,int>>> g(V);

    g[0].push_back({1,10});
    g[1].push_back({0,10});

    g[0].push_back({3,30});
    g[3].push_back({0,30});

    g[0].push_back({2,15});
    g[2].push_back({0,15});

    g[1].push_back({3,40});
    g[3].push_back({1,40});
    
    g[2].push_back({3,50});
    g[3].push_back({2,50});

prims(V,g);

}