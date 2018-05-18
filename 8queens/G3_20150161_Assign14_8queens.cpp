// GROUP:   3
// ID:      20150161
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
using namespace std;

#define MAX_COMPUTERS 15

int     best_val = 0;
bool	col_taken[MAX_COMPUTERS];
bool    fdiag_taken[MAX_COMPUTERS * 2 - 1];
bool    bdiag_taken[MAX_COMPUTERS * 2 - 1];
bool    input_board[MAX_COMPUTERS][MAX_COMPUTERS];

int     numberOfTestCases;
// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
//Access O(1)
void Remove(int i)
{
    F[B[i]]=F[i];
    B[F[i]]=B[i];
}

void Restore(int i)
{
    B[F[i]]=i;
    F[B[i]]=i;
}

void InitDancingLinks(int n)
{
    int i;
    for(i=0; i<n; i++) F[i]=i+1;
    F[n]=0;
    for(i=n; i>0; i--) B[i]=i-1;
    B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

void Backtrack(int r)
{
    if(r == numberOfTestCases)
    {
        best_val++;
        return;
    }
    for (int j = F[numberOfTestCases]; j != numberOfTestCases; j = F[j])
    {
        //cout<<j<<"<J-------"<<r<<"<R-----"<<endl;
        if(!col_taken[j] && !fdiag_taken[r + j] && !bdiag_taken[r - j + numberOfTestCases] && input_board[r][j])
        {
            fdiag_taken[r + j] = true;
            bdiag_taken[r - j + numberOfTestCases] = true;
            col_taken [j]  = true;

            Remove(j);
            Backtrack(r+1);
            Restore(j);

            fdiag_taken[r + j] = false;
            bdiag_taken[r - j + numberOfTestCases] = false;
            col_taken [j]  = false;
        }
    }
} // backtrack using dancing links
void Compute(int n)
{
    InitDancingLinks(n);
    Backtrack(0);
} // do necessay initializations and call Backtrack2()

void Compute()
{
    int numberOfCases = 1;
    cin>>numberOfTestCases;
    char input;

    while(numberOfTestCases != 0)
    {
        best_val = 0;
        for(int i = 0; i < 15; i++)
        {
            for(int j = 0; j < 15; j++)
            {
                input_board[i][j] = false;
            }
        }

        for(int i = 0; i < MAX_COMPUTERS * 2 - 1; i ++)
        {
            fdiag_taken[i] = false;
            bdiag_taken[i] = false;
        }
        for(int i = 0; i < 15; i++)
        {
            col_taken[i] = false;
        }

        for(int i = 0; i < numberOfTestCases; i++)
        {
            for(int j = 0; j < numberOfTestCases; j++)
            {
                cin>>input;
                if(input == '.')
                {
                    input_board[i][j] = true;
                }
            }
        }
        cout<<"Case "<<numberOfCases++<<": ";
        Compute(numberOfTestCases);
        cout<<best_val<<endl;
        cin>>numberOfTestCases;
    }
}

int main()
{
    freopen("input_assign13_00216.txt", "w", stdout);
    Compute();
    return 0;
}
