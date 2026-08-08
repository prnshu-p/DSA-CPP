#include <bits/stdc++.h>
using namespace std;

int main() {
    // 1. The input array
    vector<int> a = {2, 1, 2, 4, 3};
    int n = a.size();
    
    // 2. The answer array (default to -1 if no greater element exists)
    vector<int> next_greater(n, -1);
    
    // 3. The VIP Room (Always store INDICES, never the actual values)
    stack<int> st;
    
    // 4. Sweep through the array
    for (int i = 0; i < n; i++) {
        
        // --- THE BOUNCER ---
        // While the room is not empty AND the person at the top is SMALLER than the new person a[i]
        while (!st.empty() && a[st.top()] < a[i]) {
            int kicked_out_index = st.top();
            st.pop();
            
            // The person who just walked in (a[i]) is the Next Greater Element 
            // for the person who just got kicked out!
            next_greater[kicked_out_index] = a[i]; // (or store the index 'i' if you need distance)
        }
        
        // --- ENTER THE ROOM ---
        // The new person is now allowed in, waiting to find THEIR next greater element
        st.push(i);
    }
    
    // Print the results
    for (int i = 0; i < n; i++) {
        cout << a[i] << " -> " << next_greater[i] << "\n";
    }
    
    return 0;
}