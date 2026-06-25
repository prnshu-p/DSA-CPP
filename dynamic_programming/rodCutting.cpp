#include <bits/stdc++.h>
std::vector<int> prize(1e5);
int dp[100005];
int func(int len)
{
    if (len == 0)
        return 0;
        if(dp[len]!=-1)return dp[len];

    int ans = 0;
    for (int i = 1; i <= len; i++)
    {
        if (len - i >= 0)
        {
            ans = std::max(ans, func(len - i) + prize[i - 1]);
        }
    }
    return dp[len]=ans;
}

int main()
{memset(dp,-1,sizeof(dp));
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> prize[i];
    }
    std::cout << func(n) << std::endl;
}