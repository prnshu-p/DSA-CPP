#include <bits/stdc++.h>
const int N = 1e5 + 7;
int k;
std::vector<int> dp(N);
std::vector<int> h(N);
int func(int i)
{
    if (i == 0)
        return 0;
    if (dp[i] != -1)
        return dp[i];

    int cost = INT_MAX;

    for (int j = 1; j <= k; j++)
    {
        if (i - j >= 0)
            cost = std::min(cost, func(i - j) + abs(h[i] - h[i - j]));
    }
    return dp[i] = cost;
}

int main()
{
    memset(dp,-1,sizeof(dp));
    int n;
    std::cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        std::cin >> h[i];
    }
    std::cout << func(n - 1) << std::endl;
}