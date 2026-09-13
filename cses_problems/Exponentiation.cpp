#include<bits/stdc++.h>

using namespace std;

long long power(long long base, long long exp) {
    long long res = 1;
    long long mod = 1000000007;
    base %= mod;
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main(){
    int n;cin>>n;
    while(n--){
        int a,b;
        cin>>a>>b;
        cout<<power(a,b)<<"\n";
    }
}