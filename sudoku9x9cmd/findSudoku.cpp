#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;


// UI definitions
const double framespeed{ 1 };// Seconds per frame.
const int runTime{0}; // Runtime in seconds, leave blank for infinite.
int branch{};
int number{};
std::chrono::time_point<std::chrono::high_resolution_clock> t_start, t_end;


const int n = 9;
int grid[n][n]{};
short solution{};
const short clues = 17; // number of clues
const short blanks{ 82 - clues };
short depth = 0;



// function to print the solved sudoku puzzle
void printsudoku()
{
        for (short i = 0; i < 9; ++i)
        {
            for (short j = 0; j < 9; ++j)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
}


void updateFrame(int frameTime)
{
    for (int i = 0; runTime == 0 || i < runTime / framespeed; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(frameTime));
        system("cls");
        printsudoku();

        cout << "Runtime: " << fixed << std::setprecision(3) << (i + 1) * framespeed << " s\n";
        cout << "Branches: " << branch << ", bps: " << branch / (i + 1) / framespeed << endl;

        cout << "Solutions: " << number;
        cout << " , nps: " << number / (i + 1) / framespeed << endl;
        cout.flush();

        // For testing ONLY
        system("pause");
    }
    exit(EXIT_SUCCESS);
}


// function to check if a value can be placed in a particular position in the grid
bool issafe(short row, short col, short num)
{
    short subrow = (row / 3) * 3;
    short subcol = (col / 3) * 3;

        // check if the same number exists in the same row or column
        for (short i = 0; i < 9; ++i) {
            if (grid[row][i] == num || grid[i][col] == num) {
                return false;
            }
        }

        // check if the same number exists in the same 3x3 subgrid
        for (short i = subrow; i < subrow + 3; ++i) {
            for (short j = subcol; j < subcol + 3; ++j) {
                if (grid[i][j] == num) {
                    return false;
                }
            }
        }

        // if the number can be placed in the current position
        return true;
}

// function to solve the sudoku puzzle
bool solvesudoku(short row, short col)
{
    ++depth;

    // find the first unassigned cell in the grid
    bool isempty = false;
    for (short i = row; i < 9 && !isempty; ++i) {
        for (short j = col; j < 9 && !isempty; ++j) {
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
        --depth;
        return true;
    }


    // try different numbers in the current cell
    for (short num = 1; num <= 9; ++num)
    {
        if (issafe(row, col, num))
        {
            // if the number is safe, assign it to the current cell
            grid[row][col] = num;

            // recursively solve the puzzle
            if (solvesudoku(row, col))
            {
                if (solution > 0) {
                    --depth;
                    solution = 2;
                    grid[row][col] = 0;
                    return true;
                }
                ++solution;
            }

            // if the puzzle cannot be solved with the current assignment, backtrack

            //NOT CORRECTLY DELETING ALL ENTRIED
            grid[row][col] = 0;
        }
    }

    // if no number can be placed in the current cell, backtrack
    --depth;
    return false;
}


short randomizegrid(short index, short prev) {
    if (index == clues) {
        solution = 0;
        solvesudoku(0, 0);
        if (solution == 1) {
            ++number;
            printsudoku();
        }
        return --index;
    }
    short viable{};

    for (short i = prev; i < blanks + index; ++i) {
        ++branch;
        for (short numb = 1; numb < 10; ++numb) {
            if (issafe(i / 9, i % 9, numb)) {
                grid[i / 9][i % 9] = numb;
                ++index;
                index = randomizegrid(index, i + 1);
                grid[i / 9][i % 9] = 0;
            } else {
                ++viable;
            }
        }
        
        
        if (viable == 9 && solution != 0) {
            return --index;
        }
    }
    return --index;
}


// main function
int main()
{

    t_start = std::chrono::high_resolution_clock::now();
    thread t1(updateFrame, framespeed);

    randomizegrid(0, 0);

    t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elasec = t_end - t_start;
    auto elapsed_seconds{ elasec.count() };

    cout << "Runtime: " << fixed << std::setprecision(5) << elasec.count() << " s\n";
    cout << "Branches: " << branch << ", bps: " << branch / elapsed_seconds << endl;

    cout << "Solutions: " << number;
    cout << " , nps: " << number / elapsed_seconds << endl;


    return 0;
}