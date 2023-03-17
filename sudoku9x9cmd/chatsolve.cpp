//#include <iostream>
//#include <string>
//#include <iomanip>
//using namespace std;
//int branch = 1;
//
//const int n = 9;
//int grid[n][n] = {
//        {1, 0, 0, 0, 0, 7, 0, 9, 0},
//        {0, 3, 0, 0, 2, 0, 0, 0, 8},
//        {0, 0, 9, 6, 0, 0, 5, 0, 0},
//
//        {0, 0, 5, 3, 0, 0, 9, 0, 0},
//        {0, 1, 0, 0, 8, 0, 0, 0, 2},
//        {6, 0, 0, 0, 0, 4, 0, 0, 0},
//
//        {3, 0, 0, 0, 0, 0, 0, 1, 0},
//        {0, 4, 0, 0, 0, 0, 0, 0, 7},
//        {0, 0, 7, 0, 0, 0, 3, 0, 0}
//};
//string rowinput;
//
//
//void definematrix() {
//    //
//    //std::cin >> rowinput;
//    //rowinput = "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
//    //for (int i = 0; i < 9; i++) {
//    //    for (int j = 0; j < 9; j++) {
//    //        grid[i][j] = int(rowinput[9 * i + j]) - 48;
//    //    }
//    //}
//    
//    for (int i = 0; i < 9; i++) {
//        for (int j = 0; j < 9; j++) {
//            cout << grid[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//// function to check if a value can be placed in a particular position in the grid
//bool issafe(int row, int col, int num)
//{
//    // check if the same number exists in the same row or column
//    for (int i = 0; i < n; i++)
//        if (grid[row][i] == num || grid[i][col] == num)
//            return false;
//
//    // check if the same number exists in the same 3x3 subgrid
//    int subrow = (row / 3) * 3;
//    int subcol = (col / 3) * 3;
//    for (int i = subrow; i < subrow + 3; i++)
//        for (int j = subcol; j < subcol + 3; j++)
//            if (grid[i][j] == num)
//                return false;
//
//    // if the number can be placed in the current position
//    return true;
//}
//
//// function to solve the sudoku puzzle
//bool solvesudoku()
//{
//    // find the first unassigned cell in the grid
//    int row = -1, col = -1;
//    bool isempty = false;
//    for (int i = 0; i < n && !isempty; i++)
//        for (int j = 0; j < n && !isempty; j++)
//            if (grid[i][j] == 0)
//            {
//                row = i;
//                col = j;
//                isempty = true;
//            }
//
//    // if no unassigned cell is found, the puzzle is solved
//    if (!isempty)
//        return true;
//
//    // try different numbers in the current cell
//    for (int num = 1; num <= n; num++)
//    {
//        if (issafe(row, col, num))
//        {
//            // if the number is safe, assign it to the current cell
//            grid[row][col] = num;
//            branch++;
//
//            // recursively solve the puzzle
//            if (solvesudoku())
//                return true;
//
//            // if the puzzle cannot be solved with the current assignment, backtrack
//            grid[row][col] = 0;
//        }
//    }
//
//    // if no number can be placed in the current cell, backtrack
//    return false;
//}
//
//// function to print the solved sudoku puzzle
//void printsudoku()
//{
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//            cout << grid[i][j] << " ";
//        cout << endl;
//    }
//}
//
//void endclock(double time_taken) {
//    cout << "runtime : " << fixed
//        << time_taken << std::setprecision(5);
//    if (time_taken == 0) {
//        time_taken = 1;
//    }
//    cout << " sec, nps: " << branch / time_taken << endl;
//}
//
//// main function
//int main()
//{
//    // initialize the sudoku puzzle
//    cout << "enter the sudoku puzzle (use 0 for empty cells):" << endl;
//    definematrix();
//
//    // measure runtime
//    time_t start, end;
//    time(&start);
//
//    // unsync the i/o of c and c++.
//    ios_base::sync_with_stdio(false);
//
//
//    // solve the sudoku puzzle
//    if (solvesudoku())
//    {
//        cout << "the solution to the sudoku puzzle is:" << endl;
//        printsudoku();
//        cout << endl << "branches traversed:" << branch << "."<< endl;
//    }
//    else
//        cout << "the sudoku puzzle cannot be solved." << endl;
//
//    time(&end);
//    double time_taken = double(end - start);
//    endclock(time_taken);
//
//    return 0;
//}