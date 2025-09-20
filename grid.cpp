#include <iostream>

/**
 * This program traverses an NxN grid and uses a recursive function to finds groups
 * within the NxN grid.Two tiles with pieces are considered to belong to the same group if they
 * are adjacent horizontally or vertically (but not diagonally).
 *
 * In the main() function each of them is printed with the following details:
 * - the group’s number (consecutively from 1 upward, as different groups are found)
 * - which cells (identified by an ‘i’ and ‘j’ pair) belong to the group
 * - the number of cells in the group (i.e., the total number of pieces that make up each individual group
 *
 * @author Johannes Nupen Theigen
 * @version 20.09.2025
 * @since 20.09.2025
 */
using namespace std;

constexpr int N = 10; // Size of the grid
constexpr int BRICK = 1; // A cell that contains a brick
constexpr int VISITED = 2; // A brick that has already been visited

/**
 * Initializes a predefined N x N grid.
 */
int grid[N][N] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
};

/**
 * Checks whether a given cell index (i, j) is valid within the grid.
 *
 * @param i the row index to check
 * @param j the column index to check
 * @return true if (i, j) lies within the grid boundaries [0, N), false otherwise
 */
bool validIndex(const int i, const int j) {
    return i >= 0 && i <= N && j >= 0 && j <= N;
}

/**
 * Recursively explores a group of connected bricks in an N x N grid.
 * Two cells are considered part of the same group if they are adjacent
 * horizontally or vertically (but not diagonally).
 *
 * @param i the row index to check
 * @param j the column index to check
 * @param groupMembers reference variable that counts the number of bricks in the group
 */
void visitGroup(const int i, const int j, int &groupMembers) {
    if (!validIndex(i, j)) return;
    if (grid[i][j] == BRICK) {
        groupMembers++; // Count the brick as part of the group
        grid[i][j] = VISITED; // Marks the brick as visited
        cout << " (" << i << ',' << j << ')'; // Prints the coordinates of the brick

        // Explore neighboring cells (right, down, left, up)
        visitGroup(i, j + 1, groupMembers);
        visitGroup(i + 1, j, groupMembers);
        visitGroup(i, j - 1, groupMembers);
        visitGroup(i - 1, j, groupMembers);
    }
}

/**
 * Main program
 * @return 0 if succesfully executed
 */
int main() {
    int groupNr = 0;

    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
            if (grid[i][j] == 1) {
                cout << "\nGroup nr. " << groupNr++ << " contains the following members: ";
                int groupMembers = 0;
                visitGroup(i, j, groupMembers);
                cout << "\n\tAnount in group: " << groupMembers;
            }
    cout << "\n\n";
    return 0;
}