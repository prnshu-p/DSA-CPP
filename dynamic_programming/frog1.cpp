#include<bits/stdc++.h>
const int N = 1e6+7;
std::vector<int> dp(N);

int func(int i,int h[]){
    if(i==0) return 0;
    if(dp[i]!=-1)return dp[i];
    int cost = INT_MAX;

    cost = std::min(cost,func(i-1,h) + abs(h[i]-h[i-1]));

   if(i>1) cost = std::min(cost,func(i-2,h) + abs(h[i]-h[i-2]));

   return dp[i]=cost;
}


int main(){
    memset(dp,-1,sizeof(dp));
int n;
std::cin>>n;
std::vector<int> h(n);
for(int i=0;i<n;i++){
    std::cin>>h[i];
}
std::cout<<func(n-1,h);
}
