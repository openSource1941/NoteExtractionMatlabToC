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

uint32_t findMissing(uint32_t a[], uint32_t b[], uint32_t n, uint32_t m);
bool zeroValidator(uint32_t a[]);
void removeDuplicates(std::vector<uint32_t> &v);
uint32_t findInSquare(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE],uint32_t pozX,uint32_t pozY);
uint32_t solveSudoku(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
void displaySudoku(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
void sudokuFinished(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);
bool validateNumber(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE],uint32_t pozX,uint32_t pozY);
bool validateSudoku(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE]);

#endif // SUDOKUSOLVERFUNCTIONS_H_INCLUDED
