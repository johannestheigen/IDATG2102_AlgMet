#include <iostream>

/**
 * This program generates all possible permutations of the elements
 * under the condition that no two consecutive numbers (differing by ±1)
 * are placed next to each other.
 *
 * @author Frode Haug (original code)
 * @author Johannes Nupen Theigen (modified version)
 * @version 26.09.2025
 * @since 26.09.2025
 */
using namespace std;

constexpr int N = 4; // Size of array to be initialized

void swapValues(int &num1, int &num2);

void display(const int arr[], int n);

void permute(int arr[], int i, int n);

void rotateLeft(int arr[], int i, int n);

/**
 * Swaps the contents of two variables passed by reference.
 *
 *  @param   num1  -  The value to be swapped with 'num2' (reference passed)
 *  @param   num2  -  The value to be swapped with 'num1' (reference passed)
 */
void swapValues(int &num1, int &num2) {
    const int temp = num1; //  Temporary variable
    num1 = num2;
    num2 = temp;
}


/**
* Displays the content of the array 'arr'
*
* @param arr - The array whose entire contents are to be printed
* @param n - Number of elements in the array (last index used is n-1)
*/
void display(const int arr[], const int n) {
    for (int i = 0; i < n; i++)
        cout << ' ' << arr[i];
    cout << '\n';
}

/**
 * Checks whether elements within the array are in a legal position.
 * Two neighbors are considered illegal if their difference equals 1
 * or -1.
 *
 * @param arr - The array to check for legal positioning.
 * @param n   - Number of elements in the array.
 * @return true if no neighboring elements differ by  ±1, false otherwise.
 */
bool legalPosition(const int arr[], const int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] - arr[i + 1] == 1 || arr[i] - arr[i + 1] == -1) {
            return false;
        }
    }
    return true;
}

/**
 * Recursively generates ALL possible permutations of the contents of 'arr'.
 *
 * @param arr - The array to permute
 * @param i - The index to which ALL SUBSEQUENT value should be moved
 * @param n - Number of elements in the array (last index used is n-1)
 * @see swap(...)
  * @see display()
 * @see rotateLeft(...)
*/
void permute(int arr[], const int i, const int n) {
    if (i == n - 1) { // Reached a new permutation:
        if (legalPosition(arr, n)) {
            display(arr, n); // Prints the contents of the array if legal
        }
    } else {
        // To permute:
        permute(arr, i + 1, n); // Keep current number 'i'.
        // Permute the rest.
        for (int t = i + 1; t < n; t++) {
            swap(arr[i], arr[t]); // Swap number 'i' in turn with
            // ALL the others following.
            permute(arr, i + 1, n); // For each of the swaps: permute
        } // the rest of the following.
        rotateLeft(arr, i, n); // Restores original array!!!
    }
}

/**
 * Left rotates an array content.
 *
 * @param arr - The array whose contents are to be (part of) rotated left
 * @param i - Lowest index to be rotated left
 * @param n - 'n-1' is the highest index to be rotated left
*/
void rotateLeft(int arr[], const int i, const int n) {
    const int venstreVerdi = arr[i];
    for (int k = i + 1; k < n; k++)
        arr[k - 1] = arr[k];
    arr[n - 1] = venstreVerdi;
}

/**
 * Main program:
*/
int main() {
    int array[N]; // Array to be permuted.

    for (int i = 0; i < N; i++)
        array[i] = i + 1; // Fills array with: 1, 2, 3, ..., N

    cout << "The following arrays are in legal positions and can be considered 'friends':\n";
    permute(array, 0, N); // Displays legal arrays

    cout << "\n\n";
    return 0;
}