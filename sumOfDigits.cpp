#include <iostream>
int main()
{
    int n, i = 0, j = 0;
    std::cin >> n;
    while (n > 0)
    {
        i = n % 10;
        j += i;
        n/= 10;
    }
    std::cout << j;
}