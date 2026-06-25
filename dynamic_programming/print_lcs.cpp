#include <bits/stdc++.h>
int main()
{
    std::string text1, text2;
    std::cin >> text1 >> text2;

    int n = text1.size(), m = text2.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++){
            if (text1[i - 1] == text2[j - 1]){
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }else{
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = n, j = m;
    std::string ans = "";
    while (i > 0 && j > 0)
    {
        if (text1[i - 1] == text2[j - 1]){
            ans.push_back(text1[i - 1]);
            i--;
            j--;
        }else if (dp[i - 1][j] > dp[i][j - 1]){
            ans.push_back(text1[i - 1]);
            i--;
        }else{
            ans.push_back(text2[j - 1]);
            j--;
        }
    }

    while (i > 0){
        ans.push_back(text1[--i]);
    }
    while (j > 0){
        ans.push_back(text2[--j]);
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << ans << std::endl;
}