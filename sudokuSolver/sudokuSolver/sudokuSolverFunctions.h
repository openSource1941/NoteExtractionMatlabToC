#ifndef SUDOKUSOLVERFUNCTIONS_H_INCLUDED
#define SUDOKUSOLVERFUNCTIONS_H_INCLUDED
#include <iostream>
#include <vector>
#include<stdlib.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include<bits/stdc++.h>
#define SUDOKU_SIZE 9
#define SQRT_SUDOKU_SIZE (sqrt(SUDOKU_SIZE))
using namespace std;

int findMissing(int a[], int b[], int n, int m);
bool zeroValidator(int a[]);
void removeDuplicates(std::vector<int> &v);
int findInSquare(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE],int pozX,int pozY);
int solveSudoku(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
void displaySudoku(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
void sudokuFinished(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
bool validateNumber(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE],int pozX,int pozY);
bool validateSudoku(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
// variables

#endif // SUDOKUSOLVERFUNCTIONS_H_INCLUDED
