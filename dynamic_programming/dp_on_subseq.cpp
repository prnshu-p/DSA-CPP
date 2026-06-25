#include <bits/stdc++.h>
bool func(int idx, int target, std::vector<int> &nums, std::vector<std::vector<int>> &dp,int &count)
{
    if (target == 0){
    count++;
        return true;}
    if (idx == 0){
        if(nums[0]==target){count++;}

        return nums[0] == target;}
    if (dp[idx][target] != -1)
        return dp[idx][target];

    bool not_take = func(idx - 1, target, nums, dp,count);
    bool take = false;
    if (target >= nums[idx])
    {
        take = func(idx - 1, target - nums[idx], nums, dp,count);
    }

    return dp[idx][target] = (take || not_take);
}

int main()
{
    std::vector<int> nums = {2,3,7,9};
    int n = nums.size();
    int count = 0;
    int sum = accumulate(nums.begin(), nums.end(), 0);
    std::vector<std::vector<int>> dp(n, std::vector<int>(sum + 1, -1));
 func(n-1,7,nums,dp,count);
    
    std::cout<<count<<std::endl;
}