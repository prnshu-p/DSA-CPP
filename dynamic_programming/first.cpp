#include <bits/stdc++.h>
const int N = 1e5 + 11;
std::vector<int> dp(N);

int fib(int n) // state of dp
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (dp[n] != -1)
        return dp[n]; // memoise

    return dp[n] = fib(n - 1) + fib(n - 2);
}

int main()
{
    memset(dp, -1, sizeof(dp));
    int n;
    std::cin >> n;
    std::cout << fib(n) << std::endl;
}