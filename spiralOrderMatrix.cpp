#include <iostream>
#include <vector>

/**
 * Reads an r x c matrix and prints its elements in spiral order.
 * Time Complexity: O(r * c)
 * Space Complexity: O(r * c) to store the matrix
 */
int main() {
    int r, c;
    if (!(std::cin >> r >> c)) {
        return 0;
    }

    // Use a 2D std::vector instead of VLA
    std::vector<std::vector<int>> matrix(r, std::vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            std::cin >> matrix[i][j];
        }
    }

    int rowStart = 0, rowEnd = r - 1;
    int colStart = 0, colEnd = c - 1;

    while (rowStart <= rowEnd && colStart <= colEnd) {
        // Top row
        for (int i = colStart; i <= colEnd; i++) {
            std::cout << matrix[rowStart][i] << " ";
        }
        rowStart++;

        // Right column
        for (int j = rowStart; j <= rowEnd; j++) {
            std::cout << matrix[j][colEnd] << " ";
        }
        colEnd--;

        // Bottom row
        if (rowStart <= rowEnd) {
            for (int k = colEnd; k >= colStart; k--) {
                std::cout << matrix[rowEnd][k] << " ";
            }
            rowEnd--;
        }

        // Left column
        if (colStart <= colEnd) {
            for (int l = rowEnd; l >= rowStart; l--) {
                std::cout << matrix[l][colStart] << " ";
            }
            colStart++;
        }
    }
    
    std::cout << "\n";
    return 0;
}
