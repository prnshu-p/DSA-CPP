#include <cstring>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int N = 2e5 + 5;
long long bit[N];

void add(int i){
for(;i<=N;i+=(i&-i)){
    bit[i]++;
}
}

void remove(int j){
for(;j<=N;j+=(j&-j)){
    bit[j]--;
}    
}

int LOG = 18;                       // 2^18 > 2e5
int findKth(long long k,int n){           // smallest index whose prefix count >= k
    int pos = 0;
    for(int pw = LOG; pw >= 0; pw--){
        int nxt = pos + (1 << pw);
        if(nxt <= n && bit[nxt] < k){   // if (bit[nxt] < k) stops it at k-1 index as it can't be equal
            pos = nxt;
            k  -= bit[nxt];             // consume the counts we passed
        }
    }
    return pos + 1;                  // first slot that pushes us to k
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> ls(n + 1);
    // vector<int> q(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ls[i];
        add(i);
    }
    for (int i = 1; i <= n; i++) {
        int q;
        cin>>q;
        int ans = findKth(q,n);
        remove(ans);
cout<<ls[ans]<<" ";
    }




}