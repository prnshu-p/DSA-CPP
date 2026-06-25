#include<iostream>
int main(){
    std::string str = "xecgvux fhijoz";

    //convert to uppercase
    for(size_t i=0;i<str.size();i++){
str[i]-=32;
    }
    std::cout<<str<<std::endl;

    //convert to lowercase
    for(size_t i=0;i<str.size();i++){
str[i]+=32;
    }
    std::cout<<str<<std::endl;

}