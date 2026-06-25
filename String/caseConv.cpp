#include<iostream>
int main(){
    std::string str = "xecgvux fhijoz";

    //convert to uppercase
    for(int i=0;i<str.size();i++){
str[i]-=32;
    }
    std::cout<<str<<std::endl;

    //convert to lowercase
    for(int i=0;i<str.size();i++){
str[i]+=32;
    }
    std::cout<<str<<std::endl;

}