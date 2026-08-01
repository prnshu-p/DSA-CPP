//->parent array: Who is your manager?
//->find(): Climb the ladder to find the Ultimate Boss. Path 
//  compression flattens the ladder so the next time it is instant!
//->unite(): Find the two Ultimate Bosses. The Boss with the bigger 
//  Clan (higher Rank) absorbs the smaller Clan.


#include<iostream>
#include<vector>
using namespace std;

class DisjoinSetUnion{
    public:
    int n;
    vector<int> parent, rank;

        DisjoinSetUnion(int n){
            this-> n = n;

            for(int i=0;i<n;i++){
                parent.push_back(i);
                rank.push_back(0);
            }
        }

        int find(int i){
            if(parent[i]==i){
                return i;
            }
            return parent[i]=find(parent[i]);
        }

        void unionByRank(int i,int j){
            int parA=find(i);
            int parB=find(j);

            if(parA==parB) return;

            if(rank[parA]<rank[parB]){
                parent[parA]=parB;
            }
            else if(rank[parA]>rank[parB]){
                parent[parB]=parA;
            }
            else{
                parent[parB]=parA;
                rank[parA]++;
            }
        }
};

int main(){
    DisjoinSetUnion dsu(6);

    dsu.unionByRank(0,2);
    cout<<dsu.find(2)<<endl;

    dsu.unionByRank(1,3);
    dsu.unionByRank(2,5);
    dsu.unionByRank(0,3);
    cout<<dsu.find(2)<<endl;

    dsu.unionByRank(0,4);

}