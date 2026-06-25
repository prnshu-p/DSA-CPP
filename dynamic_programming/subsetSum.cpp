#include <bits/stdc++.h>
int dp[1005][100005];
bool func(int idx, int sum, std::vector<int> &val){
    if (sum == 0)
        return true;
    if (idx < 0)
        return false;
    if (dp[idx][sum] != -1)
        return dp[idx][sum];

    bool isp = func(idx - 1, sum, val);
    if(sum-val[idx]>=0){
    isp |= func(idx - 1, sum - val[idx], val);}

    return dp[idx][sum] = isp;
}

int main(){
    memset(dp, -1, sizeof(dp));
    int n, x;
    std::cin >> n >> x;

    std::vector<int> val(n);
    for (int i = 0; i < n; i++){
        std::cin >> val[i];
    }
    std::cout << func(n, x, val) << std::endl;
}