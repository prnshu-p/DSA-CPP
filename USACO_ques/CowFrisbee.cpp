#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<int> h(n);
    for(int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    
   long long total_distance = 0;
    
    stack<int> s; 
    
    for(int i = 0; i < n; ++i) {
        
        while(!s.empty() && h[s.top()] < h[i]) {
            int prev = s.top();
            s.pop();
            total_distance += (i - prev + 1);
        }
        
        if(!s.empty()) {
            total_distance += (i - s.top() + 1);
        }
        
        s.push(i);
    }
    
    cout << total_distance << "\n";
    
    return 0;
}