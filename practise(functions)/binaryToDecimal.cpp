#include<iostream>
#include <cmath>
#include<string>
int main(){
    std::string n;
    std::cin>>n;

    int ans=0;
    int p = 0;

    for(int i=n.length()-1;i>=0;i--){
        int val = n[i]-'0';
    ans+=(val*pow(2,p));
      p++;
    }
    std::cout<<ans;

}