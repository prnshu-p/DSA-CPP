#include <iostream>
#include <vector>
#include <limits.h>
#include <vector>
#include <cmath>
int main()
{
    int t, n, pd = 0;
    std::cin >> t;

    for (int i = 0; i < t; i++)
    {
        std::cin >> n;
        std::vector<int> arr(n);
        std::vector<int> currSubArr;
        std::vector<int> maxArr;

        for (int j = 0; j < n; j++)
        {
            std::cin >> arr[j];
        }
        int idx = 0;
        if (n < 3)
        {
            std::cout << n << std::endl;
        }
        else
        {
            pd = arr[0] - arr[1];
            currSubArr.push_back(arr[0]);
            currSubArr.push_back(arr[1]);
            for (int i = 1; i < n - 1; i++)
            {
                if (pd == arr[i] - arr[i + 1])
                {

                        currSubArr.push_back(arr[i + 1]);
                    

                    if (maxArr.size() < currSubArr.size())
                    {
                        maxArr = currSubArr;
                    }
                }
                else
                {
                    currSubArr.clear();
                    currSubArr.push_back(arr[i]);
                    currSubArr.push_back(arr[i + 1]);
                    if (maxArr.size() < currSubArr.size())
                    {
                        maxArr = currSubArr;
                    }
                    pd = arr[i] - arr[i + 1];
                }
            }
            std::cout << maxArr.size() << std::endl;
        }
    }
}
