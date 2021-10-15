#include "sudokuSolverFunctions.h"
const uint32_t sqrt_sudoku_size=SQRT_SUDOKU_SIZE;
uint32_t findMissing(uint32_t a[], uint32_t b[], uint32_t n, uint32_t m)
{
    for (uint32_t i = 0; i < n; i++)
    {
        uint32_t j;
        uint32_t counter = 0;
        for (j = 0; j < m; j++)
        {
            if (a[i] == b[j])
            {
                counter++;
            }
        }
        if(counter == 0)
        {
            return a[i];
        }
    }
}

bool zeroValidator(uint32_t a[])
{
    bool isTrue = false;
    for (uint32_t i = 0; i < SUDOKU_SIZE; i++)
    {
        if(a[i] == 0)
        {
            isTrue = true;
        }
    }
    return isTrue;
}


void removeDuplicates(std::vector<uint32_t> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it)
    {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}

uint32_t findInSquare(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE], uint32_t pozX, uint32_t pozY)
{
    uint32_t arrayOfNumbers[10] = {0,1,2,3,4,5,6,7,8,9};

    vector<uint32_t> a;
    for(uint32_t i = 0; i < SUDOKU_SIZE; i++)
    {
        a.push_back(puzzle[pozX][i]);
        a.push_back(puzzle[i][pozY]);
    }
    for(uint32_t i = 0; i < sqrt_sudoku_size; i++)
    {
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 0]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 1]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 2]);
    }

    sort(a.begin(), a.end());
    removeDuplicates(a);
    uint32_t sizeArray = a.size();
    uint32_t allNumbersConcerned[sizeArray];

    for(uint32_t i = 0; i < sizeArray; i++)
    {
        allNumbersConcerned[i] = a[i];
    }

    uint32_t missingNumber = 0;
    if (sizeArray >= SUDOKU_SIZE)
    {
        missingNumber = findMissing(arrayOfNumbers, allNumbersConcerned, 10, SUDOKU_SIZE);
    }

    a.clear();
    return missingNumber;
}

uint32_t solveSudoku(uint32_t puzzle [SUDOKU_SIZE][SUDOKU_SIZE])
{
    while ( zeroValidator(puzzle[0]) || zeroValidator(puzzle[1])  || zeroValidator(puzzle[2]) || zeroValidator(puzzle[sqrt_sudoku_size]) || zeroValidator(puzzle[4]) || zeroValidator(puzzle[5]) || zeroValidator(puzzle[6]) || zeroValidator(puzzle[7]) || zeroValidator(puzzle[8]))
    {
        for(uint32_t i = 0; i < SUDOKU_SIZE; i++)
        {
            for(uint32_t j = 0; j < SUDOKU_SIZE; j++)
            {
                if (puzzle[i][j] == 0)
                {
                    puzzle[i][j] = findInSquare(puzzle, i, j);
                }
            }
        }
    }
}

void displaySudoku(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(uint32_t i = 0; i < SUDOKU_SIZE; i++)
    {
        for(uint32_t j = 0; j < SUDOKU_SIZE; j++)
        {
            cout<< puzzle[i][j]<<"  ";
        }
        cout<<endl;
    }
}

void sudokuFinished(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(uint32_t i =0 ; i < SUDOKU_SIZE; i++)
    {
        for(uint32_t j = 0; j < SUDOKU_SIZE; j++)
        {
            if(puzzle[i][j] == 0)
            {
                cout<<endl<<"Sudoku is not finished"<<endl;
                return;
            }
        }
    }
    cout<<endl<<"Sudoku is finished"<<endl;
}

bool validateNumber(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE], uint32_t pozX, uint32_t pozY)
{
    vector<uint32_t> a;
    uint32_t validationArray[SUDOKU_SIZE*sqrt_sudoku_size];
    a.clear();
    for(uint32_t i = 0; i < SUDOKU_SIZE; i++)
    {
        a.push_back(puzzle[pozX][i]);
        a.push_back(puzzle[i][pozY]);
    }
    for(uint32_t i = 0; i < sqrt_sudoku_size; i++)
    {
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 0]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 1]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 2]);
    }

    sort(a.begin(), a.end());

    for(uint32_t i = 0; i < SUDOKU_SIZE*sqrt_sudoku_size; i++)
    {
        validationArray[i] = a[i];
        if((i-i%sqrt_sudoku_size)/sqrt_sudoku_size+1 != validationArray[i])
        {
            return false;
        }
    }
    return true;
}

bool validateSudoku(uint32_t puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(uint32_t i = 0; i < SUDOKU_SIZE; i++)
    {
        for(uint32_t j = 0; j < SUDOKU_SIZE; j++)
        {
            if(validateNumber(puzzle,i,j) != true)
            {
                cout<<endl<<"Sudoku is not filled correctly"<<endl;
                return false;
            }
        }
    }
    cout<<endl<<"Sudoku is filled correctly"<<endl;
}



