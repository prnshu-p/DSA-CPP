#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Sorts an array using the Count Sort algorithm.
 * Time Complexity: O(n + k), where k is the maximum element
 * Space Complexity: O(n + k)
 */
void countSort(const std::vector<int>& arr) {
    if (arr.empty()) return;
    
    int n = arr.size();
    int k = arr[0];
    for (int i = 1; i < n; i++) {
        k = std::max(k, arr[i]);
    }

    std::vector<int> count(k + 1, 0);

    // Store count of each element
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // Determine positions (cumulative sum of counts)
    // Note: This logic assumes 0-based index but stores actual position logic.
    std::vector<int> pos(k + 1, 0);
    for (int i = 1; i <= k; i++) {
        pos[i] = pos[i - 1] + count[i - 1];
    }

    std::vector<int> output(n);
    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[pos[arr[i]]] = arr[i];
        pos[arr[i]]++;
    }

    std::cout << "Count: ";
    for (int i = 0; i <= k; i++) {
        std::cout << count[i] << " ";
    }

    std::cout << "\nPos: ";
    for (int i = 0; i <= k; i++) {
        std::cout << pos[i] << " ";
    }

    std::cout << "\nSorted: ";
    for (int i = 0; i < n; i++) {
        std::cout << output[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> arr = {1, 3, 2, 3, 4, 1, 6, 4, 3};
    countSort(arr);
    return 0;
}
