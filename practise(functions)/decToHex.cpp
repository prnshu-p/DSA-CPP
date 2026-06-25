#include <iostream>
#include <cmath>
#include <std::string>
#include <algorithm>
int main()
{
    std::string ans;
    int idx=0,n,r;
    std::cin >> n;

    if (n == 0)
    {
        std::cout << 0 << std::endl;
    }

    while(n>0){
r=n%16;
if(r==10){
    ans+='A';
}else if(r==11){
  ans+='B';
}else if(r==12){
  ans+='C';
}else if(r==13){
  ans+='D';
}else if(r==14){
  ans+='E';
}else if(r==15){
  ans+='F';
}else{
ans+=to_string(r);
}
        n/=16;
    }
    std::reverse(ans.begin(), ans.end());
    std::cout<<ans<<std::endl;
}