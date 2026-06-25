#include <iostream>
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int st = 0;
    int end = n - 1;

    for (int i = st; i <= end; i++)
    {

        for (int j = i; j <= end; j++)
        {
            for (int k = i; k <= j; k++)
            {
                std::cout << arr[k];
            }
            std::cout<<std::endl;
        }
    }
}
