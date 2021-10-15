#include "sudokuSolverFunctions.h"
const int sqrt_sudoku_size=SQRT_SUDOKU_SIZE;
int findMissing(int a[], int b[], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        int j;
        int counter=0;
        for (j = 0; j < m; j++)
        {
            if (a[i] == b[j])
            {
                counter++;
            }
        }
        if(counter==0)
        {
            return a[i];
        }
    }
}

bool zeroValidator(int a[])
{
    for (int i=0; i<SUDOKU_SIZE; i++)
    {
        if(a[i]==0)
        {
            return true;
        }
    }
    return false;
}


void removeDuplicates(std::vector<int> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it)
    {
        end = std::remove(it + 1, end, *it);
    }

    v.erase(end, v.end());
}

int findInSquare(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE],int pozX,int pozY)
{
    int listaBrojeva[10]= {0,1,2,sqrt_sudoku_size,4,5,6,7,8,SUDOKU_SIZE};

    vector<int> a;
    for(int i=0; i<SUDOKU_SIZE; i++)
    {
        a.push_back(puzzle[pozX][i]);
        a.push_back(puzzle[i][pozY]);
    }
    for(int i=0; i<sqrt_sudoku_size; i++)
    {
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 0]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 1]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 2]);
    }

    sort(a.begin(), a.end());
    removeDuplicates(a);
    int sizeArray=a.size();
    int lista[sizeArray];

    for(int i=0; i<sizeArray; i++)
    {
        lista[i]=a[i];
    }

    int missingNumber=0;
    if (sizeArray>=SUDOKU_SIZE)
    {
        missingNumber=findMissing(listaBrojeva,lista,10,SUDOKU_SIZE);
    }

    a.clear();
    return missingNumber;
}

int solveSudoku(int puzzle [SUDOKU_SIZE][SUDOKU_SIZE])
{
    while ( zeroValidator(puzzle[0]) || zeroValidator(puzzle[1])  || zeroValidator(puzzle[2]) || zeroValidator(puzzle[sqrt_sudoku_size])  || zeroValidator(puzzle[4]) ||  zeroValidator(puzzle[5]) || zeroValidator(puzzle[6])|| zeroValidator(puzzle[7]) || zeroValidator(puzzle[8]))
    {
        for(int i=0; i<SUDOKU_SIZE; i++)
        {
            for(int j=0; j<SUDOKU_SIZE; j++)
            {
                if (puzzle[i][j]==0)
                {
                    puzzle[i][j]=findInSquare(puzzle,i,j);
                }
            }
        }
    }
}
void displaySudoku(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(int i=0; i<SUDOKU_SIZE; i++)
    {
        for(int j=0; j<SUDOKU_SIZE; j++)
        {
            cout<< puzzle[i][j]<<"  ";
        }
        cout<<endl;
    }
}
void sudokuFinished(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(int i =0;i< SUDOKU_SIZE;i++)
    {
        for(int j=0;j<SUDOKU_SIZE;j++)
        {
            if(puzzle[i][j]==0)
            {
                cout<<endl<<"Sudoku is not finished"<<endl;
                return;
            }
        }
    }
    cout<<endl<<"Sudoku is finished"<<endl;
}

bool validateNumber(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE],int pozX,int pozY)
{
 vector<int> a;
 int validationArray[SUDOKU_SIZE*sqrt_sudoku_size];
    a.clear();
    for(int i=0; i<SUDOKU_SIZE; i++)
    {
        a.push_back(puzzle[pozX][i]);
        a.push_back(puzzle[i][pozY]);
    }
    for(int i=0; i<sqrt_sudoku_size; i++)
    {
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 0]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 1]);
        a.push_back(puzzle[pozX - pozX % sqrt_sudoku_size + i][pozY - pozY % sqrt_sudoku_size + 2]);
    }

    sort(a.begin(), a.end());

    for(int i=0;i<SUDOKU_SIZE*sqrt_sudoku_size;i++)
    {
        validationArray[i]=a[i];
        if((i-i%sqrt_sudoku_size)/sqrt_sudoku_size+1 != validationArray[i])
        {
            return false;
        }
    }
    return true;
}
bool validateSudoku(int puzzle[SUDOKU_SIZE][SUDOKU_SIZE])
{
    for(int i=0;i<SUDOKU_SIZE;i++)
    {
        for(int j=0;j<SUDOKU_SIZE;j++)
        {
            if(validateNumber(puzzle,i,j)!=true)
            {
                            cout<<endl<<"Sudoku is not filled correctly"<<endl;
                    return false;
            }
        }
    }
        cout<<endl<<"Sudoku is filled correctly"<<endl;
}



