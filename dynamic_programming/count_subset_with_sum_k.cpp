#include <bits/stdc++.h>
int func(int idx, int target, std::vector<int> &v, std::vector<std::vector<int>> &dp) {
    if (target == 0) return 1; // found a valid subset
    if (idx == 0) return (v[0] == target);

    if (dp[idx][target] != -1) return dp[idx][target];

    int not_take = func(idx - 1, target, v, dp);
    int take = 0;
    if (target >= v[idx]) {
        take = func(idx - 1, target - v[idx], v, dp);
    }

    return dp[idx][target] = take + not_take; // total ways
}

int main() {
    int n, target;
    std::cin >> n >> target;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];

    std::vector<std::vector<int>> dp(n, std::vector<int>(target + 1, -1));
    std::cout << func(n - 1, target, v, dp) << std::endl;
}
