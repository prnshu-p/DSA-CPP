#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;
int BLOCK_SIZE;

int a[MAXN];
int next_hole[MAXN]; 
int jumps[MAXN];     
int last_hole[MAXN]; 

int n, m;

int get_block(int i) { return (i - 1) / BLOCK_SIZE; }
int get_start(int b) { return b * BLOCK_SIZE + 1; }
int get_end(int b) { return min(n, (b + 1) * BLOCK_SIZE); }

void rebuild_block(int b) {
    int start = get_start(b);
    int end = get_end(b);
    
    for (int i = end; i >= start; i--) {
        int target = i + a[i];
        
        if (target > end) {
            next_hole[i] = target;
            jumps[i] = 1;
            last_hole[i] = i;
        } 
        else {
            next_hole[i] = next_hole[target];
            jumps[i] = 1 + jumps[target];
            last_hole[i] = last_hole[target]; 
        }
    }
}

void query(int curr) {
    int total_jumps = 0;
    int last_visited = curr;
    
    while (curr <= n) {
        total_jumps += jumps[curr];
        last_visited = last_hole[curr]; 
        curr = next_hole[curr];         
    }
    
    cout << last_visited << " " << total_jumps << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;
    
    BLOCK_SIZE = sqrt(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int total_blocks = get_block(n) + 1;
    for (int b = 0; b < total_blocks; b++) {
        rebuild_block(b);
    }

    while (m--) {
        int type;
        cin >> type;
        
        if (type == 0) {
            int idx, val;
            cin >> idx >> val;
            a[idx] = val;
            
            rebuild_block(get_block(idx));
        } else {
            int idx;
            cin >> idx;
            query(idx);
        }
    }

    return 0;
}