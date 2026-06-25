#include <iostream>
#include <vector>

/**
 * Prints all prime numbers up to n using the Sieve of Eratosthenes algorithm.
 * Time Complexity: O(n * log(log(n)))
 * Space Complexity: O(n)
 */
void sieve(int n) {
    if (n < 2) return;
    
    // Use std::vector instead of VLA. Size n + 1 to access index n safely.
    // 0 means prime, 1 means not prime (or we could use a boolean vector).
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}

/**
 * Prints the prime factorization of a number using the Smallest Prime Factor (SPF) method.
 * Time Complexity: Precomputation O(n * log(log(n))), Factorization O(log n)
 * Space Complexity: O(n)
 */
void primeFactor(int n) {
    if (n < 2) return;

    // smallest_prime_factor[i] stores the smallest prime factor of i
    std::vector<int> smallest_prime_factor(n + 1);
    for (int i = 0; i <= n; i++) {
        smallest_prime_factor[i] = i;
    }

    for (int i = 2; i * i <= n; i++) {
        if (smallest_prime_factor[i] == i) {
            for (int j = i * i; j <= n; j += i) {
                if (smallest_prime_factor[j] == j) {
                    smallest_prime_factor[j] = i;
                }
            }
        }
    }

    while (n != 1) {
        std::cout << smallest_prime_factor[n] << " ";
        n /= smallest_prime_factor[n];
    }
    std::cout << "\n";
}

int main() {
    int n = 50;
    std::cout << "Primes up to " << n << ":\n";
    sieve(n);
    
    std::cout << "Prime factorization of " << n << ":\n";
    primeFactor(n);
    
    return 0;
}