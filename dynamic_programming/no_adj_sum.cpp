#include <bits/stdc++.h>
int dp[10005];
int nas(int idx, std::vector<int> &v)
{
    if (idx == 0){
        return v[0];
    }
    if (idx < 0){
        return 0;
    }
    if (dp[idx] != -1){
        return dp[idx];
    }

    int pick = v[idx] + nas(idx - 2, v);
    int not_pick = nas(idx - 1, v);

    return dp[idx] = std::max(0, std::max(pick, not_pick));
}

int main()
{
    memset(dp, -1, sizeof(dp));
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
    std::cout << nas(n - 1, v) << std::endl;
}