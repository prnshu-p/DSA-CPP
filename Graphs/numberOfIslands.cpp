#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void bfs(int r, int c, vector<vector<char>>& grid, vector<vector<bool>>& vis) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;
        q.push({r, c});
        vis[r][c] = true;
        
        int dRow[] = {-1, 1, 0, 0};
        int dCol[] = {0, 0, -1, 1};
        
        while(!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for(int i = 0; i < 4; i++) {
                int nRow = row + dRow[i];
                int nCol = col + dCol[i];
                
                if(nRow >= 0 && nRow < m && nCol >= 0 && nCol < n 
                   && grid[nRow][nCol] == '1' && !vis[nRow][nCol]) {
                    
                    vis[nRow][nCol] = true; // Paint it RED!
                    q.push({nRow, nCol});
                }
            }
        }
    }
    
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        int islandCount = 0;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                
                if(grid[i][j] == '1' && !vis[i][j]) {
                    islandCount++; 
                    
                    bfs(i, j, grid, vis); 
                }
            }
        }
        
        return islandCount;
    }
};

int main() {
    Solution sol;
    vector<vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    
    vector<vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    
    cout << "Islands in Grid 1: " << sol.numIslands(grid1) << endl; // Should be 1
    cout << "Islands in Grid 2: " << sol.numIslands(grid2) << endl; // Should be 3
    
    return 0;
}
