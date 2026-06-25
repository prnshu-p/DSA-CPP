#include <iostream>
int main()
{
    int n, t;
    std::cin >> n;
    //upperpart
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
            if(i - j + 1 == 1){
            std::cout << "*";
        }else{
            std::cout<<" ";
        }
    }
        while (t > 1)
        {
            t--;
            if(t == 1){

                std::cout << "*";
            }else{
                std::cout<<" ";
            }
        }

        std::cout << "\n";
    }
    
    //lowerpart
    for (int i = n; i>= 1; i--)
    {
        t = i;
        for (int j = n; j >= 1; j--)
        {
            while (j > i)
            {
                std::cout << " ";
                j--;
            }
            if(i - j + 1 == 1){
            std::cout << "*";
        }else{
            std::cout<<" ";
        }
    }
        while (t > 1)
        {
            t--;
            if(t == 1){

                std::cout << "*";
            }else{
                std::cout<<" ";
            }
        }

        std::cout << "\n";
    }
}