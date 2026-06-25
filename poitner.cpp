#include<iostream>
int main(){
    int a=10;
    int* ptr = &a;
    int** ptr2 = &ptr;

    std::cout<<ptr<<std::endl;
    std::cout<<ptr2<<std::endl;
    std::cout<<*(ptr)<<std::endl;
    std::cout<<*(ptr2)<<std::endl;

}