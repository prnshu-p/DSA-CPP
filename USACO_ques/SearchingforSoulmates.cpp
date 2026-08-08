#include<bits/stdc++.h>
using namespace std;

long long opr(long long a, long long b){
    // Base Case: Soulmates found!
    if(a == b) return 0;
    
    if(a > b) {
        if(a % 2 == 1) {
            return 2 + opr((a + 1) / 2, b);
        } else {
            return 1 + opr(a / 2, b);
        }
    }
    
    long long direct_add = b - a;
    
    long long div_cost = (b % 2 == 1) ? 2 : 1; 
    
    long long path_cost = div_cost + opr(a, b / 2);
    
    return min(direct_add, path_cost);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if(cin >> n) {
        for(int i = 0; i < n; i++){
            long long a, b;
            cin >> a >> b;
            cout << opr(a, b) << "\n";
        }
    }
    return 0;
}