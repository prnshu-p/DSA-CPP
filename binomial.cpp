#include<iostream>
int fact(int n){
    int f=1;
if (n < 2)
    {
        return 1;
    }
    else
    {
        for (int i =2; i <=n;i++)
        { 
          f*=i;
        }
        return f;
    }
}

int nCr(int n,int r){
    int num = fact(n);
    int deno = fact(r)*fact(n-r);

    return num/deno;
}

int main(){
    int n,r;
    std::cout<<"n=";
    std::cin>>n;
    std::cout<<"r=";
    std::cin>>r;

std::cout<<nCr(n,r);
}