#include <iostream>
#include <vector>

using namespace std;

const int MAX_NODES = 200005; 

int parent_node[MAX_NODES];
long long set_sum[MAX_NODES];
int set_count[MAX_NODES];
int id[MAX_NODES];

// Standard DSU Find with path compression
int findSet(int i) {
    if (parent_node[i] == i) return i;
    return parent_node[i] = findSet(parent_node[i]);
}

int main() {
    // Optimize standard I/O operations for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    // The input is terminated by end-of-file (EOF)
    while (cin >> n >> m) {
        
        // 1. Initialization
        int next_node = n + 1;
        for (int i = 1; i <= n; i++) {
            id[i] = i;
            parent_node[i] = i;
            set_sum[i] = i;
            set_count[i] = 1;
        }

        // Process m commands
        for (int i = 0; i < m; i++) {
            int type;
            cin >> type;

            if (type == 1) {
                int p, q;
                cin >> p >> q;
                int rootP = findSet(id[p]);
                int rootQ = findSet(id[q]);
                
                if (rootP != rootQ) {
                    parent_node[rootP] = rootQ;
                    set_sum[rootQ] += set_sum[rootP];
                    set_count[rootQ] += set_count[rootP];
                }
            } 
            else if (type == 2) {
                int p, q;
                cin >> p >> q;
                int rootP = findSet(id[p]);
                int rootQ = findSet(id[q]);
                
                if (rootP != rootQ) {
                    // Remove p from its current set's statistics
                    set_sum[rootP] -= p;
                    set_count[rootP]--;
                    
                    // Remap p to a new virtual node
                    id[p] = next_node++;
                    
                    // Initialize the new node and attach to q's set
                    parent_node[id[p]] = rootQ;
                    set_sum[rootQ] += p;
                    set_count[rootQ]++;
                }
            } 
            else if (type == 3) {
                int p;
                cin >> p;
                int rootP = findSet(id[p]);
                // Output 2 integers: the number of elements and the sum of elements
                cout << set_count[rootP] << " " << set_sum[rootP] << "\n";
            }
        }
    }
    return 0;
}  