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
using namespace std;

int findMissing(int a[], int b[], int n, int m);
bool zeroValidator(int a[]);
void removeDuplicates(std::vector<int> &v);
int findInSquare(int puzzle[9][9],int pozX,int pozY);
int solveSudoku(int puzzle[9][9]);
void displaySudoku(int puzzle[9][9]);
void sudokuFinished(int puzzle[9][9]);
bool validateNumber(int puzzle[9][9],int pozX,int pozY);
bool validateSudoku(int puzzle[9][9]);
// variables

#endif // SUDOKUSOLVERFUNCTIONS_H_INCLUDED
