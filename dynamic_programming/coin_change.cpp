#include <bits/stdc++.h>
int dp1[10010];
int cc1(int amt, std::vector<int> &coins){
    if (amt == 0) return 0;
    if (dp1[amt] != -1)return dp1[amt];

    int ans = INT_MAX;
    for (auto coin : coins)
    {
        if (amt - coin >= 0)
            ans = std::min(ans + 0ll, cc1(amt - coin, coins) + 1ll);
    }
    return dp1[amt] = ans;
}

int dp2[310][10010];
int cc2(int ind, int amt, std::vector<int>& coins){
    if (amt == 0)return 1;
    if (ind < 0)return 0;
    if(dp2[ind][amt]!=-1)return dp2[ind][amt];

    int ways = 0;
     for (int cm = 0; cm * coins[ind] <= amt; cm++) {
        ways += cc2(ind - 1, amt - cm * coins[ind], coins);
    }

    return dp2[ind][amt]=ways;
} 
int main()
{
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    int n, k;
    std::cin >> n >> k;
    std::vector<int> coins(k);
    for (int i = 0; i < k; i++)
    {
        std::cin >> coins[i];
    }
    int ans1 = cc1(n, coins);
    std::cout << (ans1 == INT_MAX ? -1 : ans1) << std::endl;
    int ans2 = cc2(k-1,n,coins);
    std::cout<<ans2<<std::endl;
}