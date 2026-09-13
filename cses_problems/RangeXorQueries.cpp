#include<bits/stdc++.h>
using namespace std;

const int N = 200005; 
long long tree[4 * N];
long long arr[N];   

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }
    
    int mid = (start + end) / 2;
    int left_child = 2 * node;
    int right_child = 2 * node + 1;
    
    build(left_child, start, mid);       
    build(right_child, mid + 1, end);      
    
    tree[node] = tree[left_child] ^ tree[right_child]; 
}

long long query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 0; // The identity value for xor addition.
    }
    
    if (l <= start && end <= r) {
        return tree[node]; 
    }
    
    // Scenario 3: Partial overlap (split and merge the answers)
    int mid = (start + end) / 2;
    long long left_ans = query(2 * node, start, mid, l, r);
    long long right_ans = query(2 * node + 1, mid + 1, end, l, r);
    
    return left_ans ^ right_ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin>>n>>q;

    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }

    build(1,1,n);

    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        cout<<query(1,1,n,a,b)<<"\n";
    }
    
    return 0;
}