#include <iostream>
#include <vector>

using namespace std;

const int MAXX = 1000000;
int freq[MAXX + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    for (int g = MAXX; g >= 1; g--) {
        int multiple_count = 0;
        
        for (int step = g; step <= MAXX; step += g) {
            multiple_count += freq[step];
        }
        
        if (multiple_count >= 2) {
            cout << g << "\n";
            return 0; 
        }
    }

    return 0;
}