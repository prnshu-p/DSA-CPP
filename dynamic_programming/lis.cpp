#include <bits/stdc++.h>
const int N = 1e5 + 7;
std::vector<int> a(N);
std::vector<int> dp(N);
int lis(int i, std::vector<int> &a){
    if (i == 0)
        return 0;
    if (dp[i] != -1)
        return dp[i];
    int ans = 1;
    for (int j = 0; j < i; j++)
    {
        if (a[i] > a[j])
        {
            ans = std::max(ans, lis(j, a) + 1);
        }
    }
    return dp[i] = ans;
}

int main(){
    memset(dp, -1, sizeof(dp));
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    int fs = 0;
    for (int i = 0; i <n; i++)
    {
        fs = std::max(fs, lis(i, a));
    }
    std::cout << fs << std::endl;
}