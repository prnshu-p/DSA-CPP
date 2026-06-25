#include <iostream>
#include <std::string>
#include <algorithm> // for std::reverse
int main() {
    int n;
    std::cin >> n;

    if (n == 0) {
        std::cout << "0";
        return 0;
    }

    std::string binary = "";

    while (n > 0) {
        binary += to_string(n % 2);  // store remainder (0 or 1)
        n /= 2;
    }

    std::reverse(binary.begin(), binary.end()); // binary is built in std::reverse

    std::cout << binary;
    return 0;
}
