#include <bits/stdc++.h>
int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];

    std::vector<int> dp(n, 1), parent(n, -1);

    int lisLength = 1, lisEnd = 0; 
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > lisLength) {
            lisLength = dp[i];
            lisEnd = i;
        }
    }

    std::vector<int> lis;
    for (int i = lisEnd; i != -1; i = parent[i])
        lis.push_back(v[i]);

    std::reverse(lis.begin(), lis.end());


    for (int x : lis) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
