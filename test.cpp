#include <bits/stdc++.h>
int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int N, M;
    std::cin >> N >> M;
    
    std::vector<std::vector<int>> grid(N + 1, std::vector<int>(M + 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            std::cin >> grid[i][j];
        }
    }
    
    int Q;
    std::cin >> Q;
    
    while (Q--) {
        int A, B, C, D;
        std::cin >> A >> B >> C >> D;
        
        bool hasZero = false;
        for (int i = A; i <= C; i++) {
            for (int j = B; j <= D; j++) {
                if (grid[i][j] == 0) {
                    hasZero = true;
                    break;
                }
            }
            if (hasZero) break;
        }
        
        if (hasZero) {
            std::cout << 0 << "\n";
        } else {
            std::cout << 1 << "\n";
        }
    }
    
    return 0;
}