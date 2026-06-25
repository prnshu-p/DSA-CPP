#include <iostream>
#include <climits>
int main() {
    int n;
    std::cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    const int N = 1e6 + 2;
    int* idx = new int[N];
    for (int i = 0; i < N; i++) {
        idx[i] = -1;
    }

    int minIdx = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (idx[arr[i]] != -1) {
            minIdx = std::min(minIdx, idx[arr[i]]);
        } else {
            idx[arr[i]] = i;
        }
    }

    if (minIdx == INT_MAX){
        std::cout << "-1\n";
    }else{
        std::cout <<  minIdx + 1 << "\n";
    }
    
    delete[] arr;
    delete[] idx;
    return 0;
}
