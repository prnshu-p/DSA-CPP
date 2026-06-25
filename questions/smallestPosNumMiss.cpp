#include <iostream>
#include <limits.h>
#include <cmath>
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int N = 1e6 + 2;
      std::vector<bool> boolarr(N);
    for (int j = 0; j < N; j++)
    {
        boolarr[j] = false;
    }

    for (int k = 0; k < n; k++)
    {
        if (arr[k] >= 0)
        {
            boolarr[arr[k]] = true;
        }
    }

    int ans = -1;
    for (int i = 0; i < N; i++)
    {
        if (boolarr[i]==false)
        {
            ans=i;
            break;
        }
    }
    std::cout << ans << std::endl;
}