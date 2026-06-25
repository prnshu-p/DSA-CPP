#include<iostream>
#include<cmath>
int main(){
    int n;
    std::cin>>n;

    int ans=0;
    for(int i=0;i<sizeof(n);i++){
      ans += (n%10)*pow(8,i);
      n/=10;
    }
    std::cout<<ans;
}