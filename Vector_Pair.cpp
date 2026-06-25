#include <iostream>
#include <algorithm>
#include <vector>

/**
 * Comparator to sort pairs by their first element.
 */
bool myCompare(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return p1.first < p2.first;
}

/**
 * Comparator to sort pairs by their second element.
 */
bool myCompare2(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
    return p1.second < p2.second;
}

int main() {
    std::vector<std::pair<int, int>> v;
    std::vector<int> arr = {14, 6, 76, 73, 4};
    int n = arr.size();

    // Store element and its original index
    for (int i = 0; i < n; i++) {
        v.push_back(std::make_pair(arr[i], i));
    }
    
    // Sort based on the elements (first element of pair)
    std::sort(v.begin(), v.end(), myCompare);

    // Replace the first element with its sorted rank (0 to n-1)
    for (int i = 0; i < n; i++) {
        v[i].first = i;
    }
    
    // Sort back based on the original index (second element of pair)
    std::sort(v.begin(), v.end(), myCompare2);

    // Print the compressed ranks
    for (int i = 0; i < n; i++) {
        std::cout << v[i].first << " ";
    }
    std::cout << "\n";
    
    return 0;
}