#include <bits/stdc++.h>
int dp [ 10005 ];
int func(int n)
{
    if (n == 0 || n==1)
    {
        return 1;
    }
    if(dp[n]!=-1)return dp[n];

    return dp[n]=func(n - 1) + func(n - 2);
}

int main()
{memset(dp,-1,sizeof(dp));
    int n;
    std::cin >> n;
    std::cout << func(n) << std::endl;
}