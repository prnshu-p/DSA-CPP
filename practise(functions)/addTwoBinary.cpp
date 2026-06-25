#include <iostream>
#include <std::string>
#include <algorithm>
int main() {
    int a, b, carry = 0, prevCarry = 0;
    std::string ans;

    std::cin >> a >> b;

    while (a > 0 || b > 0) {
        int bitA = a % 10;
        int bitB = b % 10;

        if (bitA == 1 && bitB == 1) {
            if (prevCarry > 0) {
                ans += '1';
                carry = 1;
            } else {
                ans += '0';
                carry = 1;
            }
        }
        else if ((bitA == 0 && bitB == 1) || (bitA == 1 && bitB == 0)) {
            if (prevCarry > 0) {
                ans += '0';
                carry = 1;
            } else {
                ans += '1';
                carry = 0;
            }
        }
        else { // both bits are 0
            if (prevCarry > 0) {
                ans += '1';
                carry = 0;
            } else {
                ans += '0';
                carry = 0;
            }
        }

        prevCarry = carry;
        a /= 10;
        b /= 10;
    }

    if (carry > 0) {
        ans += carry + '0';
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << ans << std::endl;

    return 0;
}
