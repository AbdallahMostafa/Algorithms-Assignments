// GROUP:   3
// ID:      20150161
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b)
{
    if(a+1==b)
    {
        T[a][b]=0;
        return 0;
    }
    if(T[a][b]>=0)
    {
        return T[a][b];
    }
    int k;
    T[a][b]=(int)1e9;
    for(k=a+1; k<b; k++)
    {
        int v= MatChain(a,k)+MatChain(k,b)+(p[a]*p[k]*p[b]);
        if(v<T[a][b])
        {
            T[a][b]=v;
            D[a][b]=k;
        }
    }
    return T[a][b];
} // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    memset(T, -1, sizeof(T));
    MatChain(0,n);
}
// BottomUp version
void MatChainBottomUp(int n)
{
    for(int s=1; s<=n; s++)
    {
        for(int i=0; i+s<=n; i++)
        {
            int j=i+s;
            if(i+1==j)
            {
                T[i][j]=0;
                continue;
            }
            T[i][j] = (int)1e9;
            for(int k=i+1; k<j; k++)
            {
                int v= T[i][k]+T[k][j]+(p[i]*p[k]*p[j]);
                if(v<T[i][j])
                {
                    T[i][j]=v;
                    D[i][j]=k;
                }
            }
        }
    }
}
// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(a+1 == b)
    {
        cout << "A" << b;
        return;
    }
    int k = D[a][b];
    cout << "(";
    MatChainSol(a, k);
    cout << " x ";
    MatChainSol(k, b);
    cout << ")";
}

void Compute()
{
	int counter = 1;
    while(true)
    {
        int numberOfTestCases;
        cin >> numberOfTestCases;
        if(numberOfTestCases == 0)
        {
            break;
        }
        for(int i=0; i<numberOfTestCases; ++i)
        {
            cin >> p[i] >> p[i+1];
        }
        MatChainBottomUp(numberOfTestCases);
        cout << "Case " << counter++ << ": ";
        MatChainSol(0, numberOfTestCases);
        cout << '\n';
    }
}

int main()
{
    //freopen("input_assign10_00348.txt", "w", stdout);
    Compute();
    return 0;
}
