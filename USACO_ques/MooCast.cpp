#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

struct Cow {
    long long x, y, p;
};

int main() {
    ifstream fin("moocast.in");
    ofstream fout("moocast.out");
    
    int N;
    fin >> N;
    
    vector<Cow> cows(N);
    for (int i = 0; i < N; ++i) {
        fin >> cows[i].x >> cows[i].y >> cows[i].p;
    }
    
    // bitset<205> provides a safety buffer over N <= 200
    bitset<205> reach[205];
    
    // Step 1: Compute direct reachability
    for (int i = 0; i < N; ++i) {
        reach[i][i] = 1; // A cow can always reach itself
        for (int j = 0; j < N; ++j) {
            long long dx = cows[i].x - cows[j].x;
            long long dy = cows[i].y - cows[j].y;
            // Squared distance check avoids float precision issues
            if (dx * dx + dy * dy <= cows[i].p * cows[i].p) {
                reach[i][j] = 1;
            }
        }
    }
    
    // Step 2: Bitset-optimized Transitive Closure (Warshall's Algorithm)
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            if (reach[i][k]) {
                reach[i] |= reach[k];
            }
        }
    }
    
    // Step 3: Find the cow that can reach the most total cows
    int max_cows = 0;
    for (int i = 0; i < N; ++i) {
        int current_reach = reach[i].count();
        if (current_reach > max_cows) {
            max_cows = current_reach;
        }
    }
    
    fout << max_cows << "\n";
    return 0;
}