#include <iostream>
#include <vector>

using namespace std;

const int N = 2e5+10; 
long long bit[N];

void update(int i, long long x){
    for(; i < N; i += (i & -i))
        bit[i] += x;
}

long long sum(int i){
    long long ans = 0;
    for(; i > 0; i -= (i & -i))
        ans += bit[i];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    
    vector<long long> arr(n + 1); 
    
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        update(i, arr[i]);
    }

    for(int i = 0; i < q; i++){
        int type, x, y;
        cin >> type >> x >> y;

        if(type == 1){
            update(x, y - arr[x]);
            arr[x] = y;
        } else {
            cout << sum(y) - sum(x - 1) << "\n";
        }
    }
    
    return 0;
}