#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <string>
using namespace std;

string grid[9][9];
string matrix[9][9];
bool solveState[9][9];
string solveStatus;
bool progress;
string rowInput;
vector<vector<int>> blanksLoc;
vector<vector<string>> possValues;
vector <int> corrMatrix;

void defineMatrix() {
	std::cin >> rowInput;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			grid[i][j] = rowInput[9 * i + j];
		}
	}
	copy(&grid[0][0], &grid[0][0] + 9 * 9, &matrix[0][0]);
}

void printMatrix(int mName) {
	switch (mName) {
	case 0:
		for (int i = 0; i < 9; i++) {
			std::cout << "\n";
			for (int j = 0; j < 9; j++) {
				std::cout << grid[i][j] << " ";
			}
		}
		break;
	case 1:
		for (int i = 0; i < 9; i++) {
			std::cout << "\n";
			for (int j = 0; j < 9; j++) {
				std::cout << matrix[i][j] << " ";
			}
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++) {
			std::cout << "\n";
			for (int j = 0; j < 9; j++) {
				std::cout << solveState[i][j] << " ";
			}
		}
		break;
	}
}


void singleSolution(int row, int col, int blankindx) {
	vector<string> solutionSpace = { "1","2","3","4","5","6","7","8","9" };
	for (int ir = 0; ir < 9; ir++) { //row
		solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[row][ir]), solutionSpace.end());
	}
	for (int ir = 0; ir < 9; ir++) { //column
		solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[ir][col]), solutionSpace.end());
	}
	int identityRow = (((int)(row / 3)) * 3);
	int identityCol = (((int)(col / 3)) * 3);
	for (int ir = 0; ir < 3; ir++) {
		for (int jr = 0; jr < 3; jr++)
			solutionSpace.erase(remove(solutionSpace.begin(), solutionSpace.end(), matrix[ir + identityRow][jr + identityCol]), solutionSpace.end());
	}
	if (solutionSpace.size() == 1) {// If only one possible number
		matrix[row][col] = solutionSpace[0];
		blanksLoc.erase(blanksLoc.begin() + blankindx);
		cout << blanksLoc.size();
		progress = 1;
	}
	else {
		possValues.push_back(solutionSpace);
	}
	// What if there is more than one number possible, but only this blankLoc can have this value?
}

bool solveMatrix() {
	do {
		progress = 0;
		for (int ic = 0; ic < 3; ic++) {
			for (int jc = 0; jc < 3; jc++) {
				int blanks = 0;
				for (int subi = 0; subi < 3; subi++) {
					for (int subj = 0; subj < 3; subj++) {
						if (matrix[ic][jc] == "0") {
							singleSolution(ic, jc, blanks);
							blanks++;
							blanksLoc.push_back({ subi + 3 * ic,subj + 3 * jc });
							solveState[subi + 3 * ic][subj + 3 * jc] = 1;
						}
					}
				}
				// Check if only one possval available.
				for (int numb = 1; numb < 10; numb++) {
					int count = 0;
					for (int blank = 0; blank < blanks; blank++) {
						vector<int>::iterator loc = find(possValues[blank].begin(), possValues[blank].end(), numb);
						if (loc != possValues[blank].end()) {
							count++;
						}
					}
					if (count == 1) {
						matrix[blanksLoc[loc][0]][blanksLoc[loc][1]] = numb;
						blanksLoc.erase(blanksLoc.begin() + loc - 1);
						possValues.erase(blanksLoc.begin() + loc - 1);
						progress = 1;
					}
				}
				corrMatrix[3 * ic + jc] = blanks;
			}
			//
			//
							/* 						vector<vector<string>>::iterator rrow = possValues.begin();
				vector<string>::iterator ccol = rrow->begin();
				vector<string>::iterator loc;
				loc = find(&possValues[blank], &possValues[blank + 1], numb);
				if (loc != &possValues[blank + 1]) {
					count++; */
					// 
			//
			//
		}
		/*		for (int i = 0; i < blanksLoc.size(); i++) { // Repeat for each blank
					int rowindx = blanksLoc[i][0];
					int colindx = blanksLoc[i][1];
					singleSolution(rowindx, colindx, i);
				}*/
	} while (progress && !blanksLoc.empty());
	return blanksLoc.empty();
}

//070020005060000700530040000013000560680050002250036190340000906726493851890060003

void verify() {
	// Verify all numbers are 0-9
	// Verify no collusions
}


int main() {
	defineMatrix();
	solveStatus = (solveMatrix()) ? "Solution Found:" : "Unsolvable.";
	cout << solveStatus;
	printMatrix(1);
	return 0;
}