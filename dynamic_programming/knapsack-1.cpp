#include <bits/stdc++.h>
long long dp[105][100005];
int val[105], wt[105];

long long knp(int idx, int wt_left)
{
    if (idx < 0 || wt_left == 0)
        return 0; // you dont know that value of semicolon
    if (dp[idx][wt_left] != -1)
        return dp[idx][wt_left];

    long long ans = knp(idx - 1, wt_left); // leave

    if (wt_left - wt[idx] >= 0)
        ans = std::max(ans, knp(idx - 1, wt_left - wt[idx]) + val[idx]); // std::max when taking it
    return dp[idx][wt_left] = ans;
}

int main()
{
    
memset(dp,-1,sizeof(dp));
int n,w;
    std::cin >> n >> w;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> wt[i] >> val[i];
    }

    long long ans1 = knp(n - 1, w);
    std::cout << ans1 << std::endl;
}
