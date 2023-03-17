#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int branch = 0;

const int N = 9;
int grid[N][N] = {};
int solGrid[N][N];
int number = 0;
int solution;
int clues = 30; // Number of clues

int depth = 0;

// Function to check if a value can be placed in a particular position in the grid
bool isSafe(int row, int col, int num)
{
    // Check if the same number exists in the same row or column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if the same number exists in the same 3x3 subgrid
    int subrow = (row / 3) * 3;
    int subcol = (col / 3) * 3;
    for (int i = subrow; i < subrow + 3; i++) {
        for (int j = subcol; j < subcol + 3; j++) {
            if (grid[i][j] == num) {
                return false;
            }
        }
    }

    // If the number can be placed in the current position
    return true;
}

// Function to solve the Sudoku puzzle
bool solveSudoku()
{
    depth++;
    if (solution > 1) {
        depth--;
        return false;
    }

    // Find the first unassigned cell in the grid
    int row = -1, col = -1;
    bool isEmpty = false;
    for (int i = 0; i < N && !isEmpty; i++) {
        for (int j = 0; j < N && !isEmpty; j++) {
            if (solGrid[i][j] == 0)
            {
                row = i;
                col = j;
                isEmpty = true;
            }
        }
    }

    // If no unassigned cell is found, the puzzle is solved
    if (!isEmpty)
    {
        depth--;
        return true;
    }



    // Try different numbers in the current cell
    for (int num = 1; num <= N; num++)
    {
        if (isSafe(row, col, num))
        {
            // If the number is safe, assign it to the current cell
            solGrid[row][col] = num;
            branch++;

            // Recursively solve the puzzle
            if (solveSudoku())
            {
                solution++;
                if (solution < 2) {
                    depth--;
                    return true;
                }
                else {
                    depth--;
                    return false;
                }
            }

            // If the puzzle cannot be solved with the current assignment, backtrack
            solGrid[row][col] = 0;
        }
    }

    // If no number can be placed in the current cell, backtrack
    depth--;
    if (depth == 0 && solution == 1) {
        return true;
    }
    return false;
}


// Function to print the solved Sudoku puzzle
void printSudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}

int randomizeGrid(int index) {
    if (number == 1000000) { index--; return index; }
    for (int i = index; i < 81 - clues + index; i++) {
        if (index < clues) {
            if (grid[i / 9][i % 9] == 0) {
                for (int numb = 1; numb < 10; numb++) {
                    if (isSafe(i / 9, i % 9, numb)) {
                        grid[i / 9][i % 9] = numb;
                        index++;
                        index = randomizeGrid(index);
                        grid[i / 9][i % 9] = 0;
                    }
                }
            }
        }
        else {
            copy(&grid[0][0], &grid[0][0] + 9 * 9, &solGrid[0][0]);
            solution = 0;
            if (solveSudoku) {
                number++;
            }
            index--;
            return index;
        }
    }
    index--;
    return index;
}


void endClock(double time_taken) {
    cout << "Runtime : " << fixed
        << time_taken << std::setprecision(5);
    if (time_taken == 0) {
        time_taken = 1;
    }
    cout << " Seconds, nps: " << branch/* / time_taken*/ << endl;
}

// Main function
int main()
{
    time_t start, end;
    time(&start);
    randomizeGrid(0);
    time(&end);
    double time_taken = double(end - start);
    endClock(time_taken);
    cout << "Solutions: " << number;
    cout << " , nps: " << number / time_taken << endl;


    return 0;
}