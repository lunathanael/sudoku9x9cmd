#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int branch = 0;
const int n = 9;
int grid[n][n] = {};
int solgrid[n][n] = {};
int number = 0;
int solution;
int clues = 17; // number of clues

int depth = 0;
w

// function to print the solved sudoku puzzle
void printsudoku(int identifier)
{
    switch (identifier) {
    case 0:
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
                cout << grid[i][j] << " ";
            cout << endl;
        }
        break;
    case 1:
        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
                cout << solgrid[i][j] << " ";
            cout << endl;
        }
        break;
    }
}


// function to check if a value can be placed in a particular position in the grid
bool issafe(int row, int col, int num)
{
    int subrow = (row / 3) * 3;
    int subcol = (col / 3) * 3;

        // check if the same number exists in the same row or column
        for (int i = 0; i < n; ++i) {
            if (grid[row][i] == num || grid[i][col] == num) {
                return false;
            }
        }

        // check if the same number exists in the same 3x3 subgrid
        for (int i = subrow; i < subrow + 3; ++i) {
            for (int j = subcol; j < subcol + 3; ++j) {
                if (grid[i][j] == num) {
                    return false;
                }
            }
        }

        // if the number can be placed in the current position
        return true;
}

// function to solve the sudoku puzzle
bool solvesudoku()
{
    depth++;
    // find the first unassigned cell in the grid
    int row = -1, col = -1;
    bool isempty = false;
    for (int i = 0; i < n && !isempty; ++i) {
        for (int j = 0; j < n && !isempty; ++j) {
            if (grid[i][j] == 0)
            {
                row = i;
                col = j;
                isempty = true;
            }
        }
    }

    // if no unassigned cell is found, the puzzle is solved
    if (!isempty)
    {
        depth--;
        return true;
    }


    // try different numbers in the current cell
    for (int num = 1; num <= n; ++num)
    {
        if (issafe(row, col, num))
        {
            // if the number is safe, assign it to the current cell
            grid[row][col] = num;
            ++branch;

            // recursively solve the puzzle
            if (solvesudoku())
            {
                if (solution > 0) {
                    depth--;
                    solution = 2;
                    grid[row][col] = 0;
                    return true;
                }
                ++solution;
            }

            // if the puzzle cannot be solved with the current assignment, backtrack
            grid[row][col] = 0;
        }
    }

    // if no number can be placed in the current cell, backtrack
    depth--;
    return false;
}


int randomizegrid(int index) {
    if (number == 1) { index--; return index; }
    for (int i = index; i < 82 - clues + index; ++i) {
        if (index < clues) {
            if (grid[i / 9][i % 9] == 0) {
                for (int numb = 1; numb < 10; ++numb) {
                    if (issafe(i / 9, i % 9, numb)) {
                        grid[i / 9][i % 9] = numb;
                        ++index;
                        index = randomizegrid(index);                       
                        grid[i / 9][i % 9] = 0;
                    }
                }
            }
        }
        else {
            solution = 0;
            if (solvesudoku()) {

            }
            if (solution == 1) {
                ++number;
                printsudoku(0);
            } else if (branch >= 100000000) {
                printsudoku(0);
                branch = 0;
            }
            index--;
            return index;
        }
    }
    index--;
    return index;
}


void endclock(double time_taken) {
    cout << "runtime : " << fixed
        << time_taken << std::setprecision(5);
    if (time_taken == 0) {
        time_taken = 1;
    }
    cout << " seconds" << endl << "branches: " << branch << ", bps: " << branch / time_taken << endl;
}

// main function
int main()
{
    time_t start, end;
    time(&start);

    randomizegrid(0);
    time(&end);
    double time_taken = double(end - start);
    endclock(time_taken);
    cout << "solutions: " << number;
    cout << " , nps: " << number / time_taken << endl;


    return 0;
}