#include <iostream>
#include <vector>
#include<stdlib.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <list>
#include<bits/stdc++.h>
#include "sudokuSolverFunctions.h"

int puzzle[SUDOKU_SIZE][SUDOKU_SIZE] =
        {{5,3,0,0,7,0,0,0,0},
          {6,0,0,1,9,5,0,0,0},
          {0,9,8,0,0,0,0,6,0},
          {8,0,0,0,6,0,0,0,3},
          {4,0,0,8,0,3,0,0,1},
          {7,0,0,0,2,0,0,0,6},
          {0,6,0,0,0,0,2,8,0},
          {2,0,0,4,1,9,0,0,5},
          {0,0,0,0,8,0,0,7,9}};

int main()
{
    displaySudoku(puzzle);
    sudokuFinished(puzzle);
    validateSudoku(puzzle);

solveSudoku(puzzle);
displaySudoku(puzzle);
sudokuFinished(puzzle);
validateSudoku(puzzle);

    return 0;
}
