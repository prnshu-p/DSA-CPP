#include <bits/stdc++.h>
long long dp[105][100005], val[105], wt[105];

long long knp(int idx, int val_left){
    if (val_left == 0)return 0;
    if (idx < 0)return 1e15;
    if (dp[idx][val_left] != -1)return dp[idx][val_left];

    long long ans = knp(idx - 1, val_left);

    if (val_left - val[idx] >= 0){
        ans = std::min(ans, knp(idx - 1, val_left - val[idx]) + wt[idx]);
    }
    return dp[idx][val_left] = ans;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    int n, w, total_val = 0;
    std::cin >> n >> w;
    for (int i = 0; i < n; i++){
        std::cin >> wt[i] >> val[i];
        total_val += val[i];
    }

    int ans = 0;
    for(int i = 0; i <= total_val; i++){
        if(knp(n - 1, i) <= w){
            ans = i;
        }
    }
    std::cout << ans << std::endl;
}