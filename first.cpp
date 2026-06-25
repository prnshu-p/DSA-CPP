#include <iostream>
int main()
{
    int n, t;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        t = i;
        for (int j = n; j >= 1; j--)
        {
            while (j > i)
            {
                std::cout << " ";
                j--;
            }
            std::cout << i - j + 1;
        }
        while (t > 1)
        {
            t--;
            std::cout << t;
        }

        std::cout << "\n";
    }
}