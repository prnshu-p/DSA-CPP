#include<iostream>
int main(){
    int a, b;
    std::cin >> a >> b;

    int rem;
    while (b != 0) {
        rem = a % b;
        a = b;
        b = rem;
    }

    std::cout << a << std::endl;
}
