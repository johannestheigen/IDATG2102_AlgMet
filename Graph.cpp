/**
 * This program uses permutation to assign valid IDs to nodes within a graph
 * that satisfies gRequiredSum. gRequiredSum requires the following:
 * if you take the sum of the IDs (numbers) for the neighbors of the one with ID no. 0
 * (it is not the one with reference no. 0 above) you get 21, if you take the sum of the IDs
 * for the neighbors of the one with ID no. 1 you get 33, and so on.
 *
 * @author Frode Haug (Original author of examples used to solve this task)
 * @author Johannes Nupen Theigen
 * @version 20.10.2025
 * @since 20.10.2025
 */
#include <iostream>
using namespace std;

constexpr int N = 10; // Number of nodes in the graph.

// Neighbor matrix
int gNeighbor[N][N] = {
    {0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
    {0, 0, 1, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 0}
};

int gRequiredSum[N] = {21, 33, 14, 27, 1, 14, 20, 12, 28, 20}; // Required sum of neighbor IDs for each node ID

void swapValues(int & num1, int & num2);

bool checkRequirements(const int arr[], int n);

void permute(int arr[], int i, int n);

void displaySolution(const int arr[]);

void rotateLeft(int arr[], int i, int n);

/**
 *  Main program:
 */
int main() {
    int array[N];
    for (int i = 0; i < N; i++)
        array[i] = i;

    permute(array, 0, N);
    cout << '\n';
    return 0;
}

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
 * Checks if the combination of IDs assigned to nodes 0–9 satisfies
 * the neighbor-sum requirements defined in gRequiredSum.
 *
 * @param arr - Array containing the node IDs to be checked
 * @param n - Number of elements in the array
 * @return true if the combination satisfies all requirements
 */
bool checkRequirements(const int arr[], const int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (gNeighbor[i][j] == 1) {
                sum+= arr[j];
            }
        }
        if (sum != gRequiredSum[arr[i]]) {
            return false;
        }
        sum = 0;
    }
    displaySolution(arr); // A valid solution has been found!
    return true;
}

/**
 * Displays the solution that satisfies gRequiredSum.
 *
 * @param arr - Array containing the IDs assigned to each node.
 */
void displaySolution(const int arr[]) {
    cout << "Solution: " << "\n";
    for (int i = 0; i < N; i++) {
            cout << "Node " << i << " assigned with " << "ID: " << arr[i] << "\n";
    }
}

/**
 * Recursively generates all possible permutations of the contents of 'arr'
 * to find a combination that satisfies gRequiredSum.
 *
 * @param arr - The array to permute
 * @param i - The index to which ALL SUBSEQUENT value should be moved
 * @param n - Number of elements in the array (last index used is n-1)
 * @see swapValues(...)
 * @see checkRequirements(...)
 * @see rotateLeft(...)
*/
void permute(int arr[], const int i, const int n) {
    if (i == n-1)                       // Reached a new permutation:
        checkRequirements(arr, n); // Checks if the permuatation satfiyes gRequiredSum
    else {                              // To permute:
        permute(arr, i+1, n);          // Keep current number 'i'.
        // Permute the rest.
        for (int t = i+1;  t < n;  t++) {
            swapValues(arr[i], arr[t]);      // Swap number 'i' in turn with
            // ALL the others following.
            permute(arr, i+1, n);      // For each of the swaps: permute
        }                              // the rest of the following.
        rotateLeft(arr, i, n);       // Restores original array!!!
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