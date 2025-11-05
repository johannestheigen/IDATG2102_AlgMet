#include <fstream>
#include <iostream>
#include <stdexcept>

/**
 * This program is solve any 9x9 sudoku puzzles.
 *
 * The program loads a sudoku sudokuGrid from a text file using
 * the function loadFromFile() implemented with the <fstream> and
 * <stdexcept> libraries.
 *
 * To solve the puzzle, the program uses the function findSolution(),
 * which applies recursion and backtracking to find a legal solution.
 *
 * A solution is considered legal if no cell contains a number
 * that already exists in its row, column, or 3x3 subgrid. A Sudoku puzzle
 * grid has only one legal solution. Once it is found, the function displaySolution()
 * is called to display the result.
 *
 * This program is inspired by example code provided by Frode Haug at NTNU,
 * which solves the same problem. Additional parts of the solution are based
 * on pseudo-code suggestions from Microsoft Copilot combined with my own
 * understanding of the underlying logic.
 *
 * @author Johannes Nupen Theigen
 * @version 05.11.2025
 * @since 05.11.2025
*/
using namespace std;

const int X = 9, Y = 9; // Dimensions of the Sudoku puzzle grid (9x9)
const int N = X * Y; // Total cells in the sudoku puzzle.

int sudokuGrid[X][Y]; // Represents a 9x9 Sudoku puzzle.

/**
 * Loads a Sudoku puzzle from the file "sudoku_grid.txt"
 * and initializes the internal grid with the values from the file.
 *
 * @throws std::runtime_error if the file cannot be opened.
 */
void loadFromFile() {
    string myText;
    ifstream file("sudoku_grid.txt");
    if (!file) {
        throw runtime_error("Could not load the file, it does not exist!");
    }
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            file >> sudokuGrid[i][j];
    file.close();
}

/**
 * Displays the solution of a Sudoku puzzle once a legal solution is found.
 */
void displaySolution() {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            cout << sudokuGrid[i][j] << "  ";
        }
        cout << "\n";
    }
}

/**
 * Recursive function that uses backtracking to find a legal solution
 * to a 9x9 Sudoku puzzle. A solution is considered legal if no cell
 * contains a number that already exists in its row, column, or 3x3 subgrid.
 *
 * @param n The index of the square to start from.
 * @return true if a legal solution is found, false otherwise.
 */
bool findSolution(const int n) {
    if (n == N) { // All cells are filled, a complete legal solution has been found!
        displaySolution();
        return true;
    }

    const int i = n / X, j = n % Y; // Calculates the row (i) and column (j) of the square to process.

    if (sudokuGrid[i][j] != 0) {
        return findSolution(n + 1); // Checks whether the current cell has already been filled.
    }

    for (int value = 1; value <= 9; value++) {
        bool legalValue = true;
        for (int row = 0; row < 9; row++) {
            if (sudokuGrid[i][row] == value) {
                legalValue = false; // Checks if the value already exists in the same row.
            }
        }

        for (int col = 0; col < 9; col++) {
            if (sudokuGrid[col][j] == value) {
                legalValue = false; // Checks if the value already exists in the same column.
            }
        }

        int startRow = (i / 3) * 3, startCol = (j / 3) * 3; // Find the top-left corner of the 3x3 subgrid for the current cell.
        for (int r = startRow; r < startRow + 3; r++) {
            for (int c = startCol; c < startCol + 3; c++) {
                if (sudokuGrid[r][c] == value) {
                    legalValue = false; // Checks if the value exists in the 3x3 subgrid.
                }
            }
        }
        if (legalValue) {
            sudokuGrid[i][j] = value; // Assign the legal value to the current cell.

            if (findSolution(n + 1)) {
                return true; // A complete solution was found after assigning this value.
            }
            sudokuGrid[i][j] = 0; // Reset the cell to empty to explore other possible values (backtracking).
        }
    }
    return false;
}

/**
 * Main program.
 *
 * @return 0 if the program executes successfully.
 */
int main() {
    try {
        loadFromFile();
        cout << "Unsolved: " << "\n";
        displaySolution();
        cout << "\n";
        cout << "Solved:" << "\n";
        findSolution(0);
    } catch (const runtime_error &e) {
        cout << e.what();
    }
    return 0;
}