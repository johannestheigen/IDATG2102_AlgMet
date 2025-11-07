/**
 * This program calculates if a number is perfect or not, and is programmed to print the first five.
 * NOTE: This program uses a lot of computation so it will spent over 8 days to print the fith one.
 *
 * A perfect number is a number that is equal to the sum of all its positive divisors,
 * excluding the number itself. The first perfect number is 6 (= 1 + 2 + 3).
 * The second is 28 (= 1 + 2 + 4 + 7 + 14).
 * The third is 496 (= 1 + 2 + 4 + 8 + 16 + 31 + 62 + 124 + 248).
 * The fourth, fifth, and sixth are: 8128, 33,550,336, and 8,589,869,056.
 *
 * This program is inspired by example code provided by Frode Haug at NTNU,
 * which solves the same problem. Additional parts of the solution are based
 * on suggestions from Microsoft Copilot combined with my own
 * understanding of the underlying logic.
 *
 * @author Johannes Nupen Theigen
 * @version 07.11.2025
 * @since 07.11.2025
 */
#include <iostream>
using namespace std;

/**
 * @brief Calculates whether a number is perfect.
 *
 * @param n The number to be checked.
 * @return true if the number is perfect, false otherwise.
 */
bool isPerfectNumber(const int n) {
    int sum = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) { // Adds the number to the sum if it is divisible.
            sum = sum + i;
        }
        if (sum > n) { // The sum has exceeded 'n'; the number is not perfect.
            return false;
        }
    }
    return (sum == n);
}

/**
 * Main program
*/
int main() {
    for (int i = 1; i <= 33550336; i++) { // Iterates through every number to the fith perfect number '33.550.336'
        if (isPerfectNumber(i)) {
            cout << i << "\n"; // Prints out the number if it's perfect.
        }
    }
    return 0;
}