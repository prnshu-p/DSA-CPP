#include <iostream>
#include <cmath>
#include <std::string>
int main()
{
    std::string n;
    std::cin >> n;
    int p = 0;

    int ans = 0;
    for (int i = n.length()-1; i >= 0; i--)
    {
        if (n[i] == 'A')
        {
            ans += 10* pow(16, p);
        }
        else if (n[i] == 'B')
        {
            ans += 11 * pow(16, p);
        }
        else if (n[i] == 'C')
        {
            ans += 12 * pow(16, p);
        }
        else if (n[i] == 'D')
        {
            ans += 13 * pow(16, p);
        }
        else if (n[i] == 'E')
        {
            ans += 14 * pow(16, p);
        }
        else if (n[i] == 'F')
        {
            ans += 15 * pow(16, p);
        }
        else
        {
            ans += (n[i] - '0') * pow(16, p);
        }
        p++;
    }
    std::cout<<ans<<std::endl;
}