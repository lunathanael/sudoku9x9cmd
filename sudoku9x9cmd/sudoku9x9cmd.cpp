//#include <iostream>
//#include <algorithm>
//#include <stdlib.h>
//#include <vector>
//#include <string>
//using namespace std;
//
//string grid[9][9];
//string matrix[9][9];
//bool solveState[9][9];
//string solveStatus;
//int progress = 1;
//string rowInput;
//vector<vector<int>> blanksLoc;
//vector<vector<string>> possValues;
//vector <int> corrMatrix;
//int blanks = 0;
//vector<string> solSpace;
//
//void defineMatrix() {
//	std::cin >> rowInput;
//	rowInput = "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
//	for (int i = 0; i < 9; i++) {
//		for (int j = 0; j < 9; j++) {
//			grid[i][j] = rowInput[9 * i + j];
//		}
//	}
//	copy(&grid[0][0], &grid[0][0] + 9 * 9, &matrix[0][0]);
//}
//
//void printMatrix(int mName) {
//	switch (mName) {
//	case 0:
//		for (int i = 0; i < 9; i++) {
//			std::cout << "\n";
//			for (int j = 0; j < 9; j++) {
//				std::cout << grid[i][j] << " ";
//			}
//		}
//		break;
//	case 1:
//		for (int i = 0; i < 9; i++) {
//			std::cout << "\n";
//			for (int j = 0; j < 9; j++) {
//				std::cout << matrix[i][j] << " ";
//			}
//		}
//		break;
//	case 2:
//		for (int i = 0; i < 9; i++) {
//			std::cout << "\n";
//			for (int j = 0; j < 9; j++) {
//				std::cout << solveState[i][j] << " ";
//			}
//		}
//		break;
//	case 3:
//		for (int i = 0; i < blanksLoc.size(); i++) {
//			std::cout << "\n";
//			for (int j = 0; j < blanksLoc[i].size(); j++) {
//				std::cout << blanksLoc[i][j] << " ";
//			}
//		}
//	}
//}
//
//
//vector<string> singleSolution(int row, int col, int blankindx) {
//	vector<string> solutionSpace = { "1","2","3","4","5","6","7","8","9" };
//	for (int ir = 0; ir < 9; ir++) { //row
//		solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[row][ir]), solutionSpace.end());
//		solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[ir][col]), solutionSpace.end());
//	}
//	int identityRow = (((int)(row / 3)) * 3);
//	int identityCol = (((int)(col / 3)) * 3);
//	for (int ir = 0; ir < 3; ir++) {
//		for (int jr = 0; jr < 3; jr++)
//			solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[ir + identityRow][jr + identityCol]), solutionSpace.end());
//	}
//	if (solutionSpace.size() == 1) {// If only one possible number
//		matrix[row][col] = solutionSpace[0];
//		cout << solutionSpace[0];
//		progress++;
//	}
//	else {
//		blanksLoc.push_back({row,col});
//		blanks++;
//
//		// Might be unneeded.
//		possValues.push_back(solutionSpace);
//	}
//	return (solutionSpace);
//	// What if there is more than one number possible, but only this blankLoc can have this value?
//}
//
//bool solveMatrix() {
//	do {
//		progress--;
//
//		for (int ic = 0; ic < 3; ic++) {
//			for (int jc = 0; jc < 3; jc++) { // checking at  3x3
//				vector<int> loc(9,0);
//				vector<int> count(9, 0);
//				blanksLoc.clear();
//				possValues.clear();
//				blanks = 0;
//				for (int subi = 0; subi < 3; subi++) {
//					for (int subj = 0; subj < 3; subj++) { // Checking in said 3x3.
//
//						if (matrix[subi + 3 * ic][subj + 3 * jc] == "0") {
//							solveState[subi + 3 * ic][subj + 3 * jc] = 1;
//							solSpace = singleSolution(subi + 3 * ic, subj + 3 * jc, blanks);
//							if (solSpace.size() > 1) {
//
//								for (int numb = 1; numb < 10; numb++) {
//									for (string trial : solSpace) {
//										if (trial == to_string(numb)) {
//											count[numb - 1]++;
//											loc[numb - 1] = blanks - 1;
//
//										}
//									}
//
//								}
//							}
//						}
//					}
//				}
//				
//				for (int numb = 1; numb < 10; numb++) {
//					numb--;
//					if (count[numb] == 1 && blanksLoc.size() > 0) {
//						matrix[blanksLoc[loc[numb]][0]][blanksLoc[loc[numb]][1]] = to_string(numb + 1);
//						cout << numb + 1;
//
//						blanksLoc.erase(blanksLoc.begin() + loc[numb]);
//						possValues.erase(possValues.begin() + loc[numb]);
//						blanks--;
//						progress++;
//					}
//					numb++;
//				// Check if only one possval available.
//
//
//					}
//				}
//				//corrMatrix[3 * ic + jc] = blanks;
//			}
//
//
//		cout << "\nCycle Complete.";
//	} while (progress > 0 && !blanksLoc.empty());
//	return blanksLoc.empty();
//}
//
////070020005060000700500040000013000000600050002250036190040000006720490051800000003
//
//void verify() {
//	// Verify all numbers are 0-9
//	// Verify no collusions
//}
//
//
//int main() {
//	defineMatrix();
//	solveStatus = (solveMatrix()) ? "Solution Found:" : "Unsolvable.";
//	cout << solveStatus;
//	printMatrix(3);
//	cout << "\n";
//	printMatrix(1);
//	return 0;
//}
