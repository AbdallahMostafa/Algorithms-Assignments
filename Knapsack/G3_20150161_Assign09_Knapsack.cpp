// GROUP:   3
// ID:      20150161
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

int T1[1001][31];
int Knapsack1(int n, int w)
{
    if (n == 0)
    {
        T1[n][w] = 0;
        return 0;
    }
    if(T1[n][w]>=0)
    {
        return T1[n][w];
    }
    T1[n][w] = Knapsack1(n-1,w);
    int cw=a[n-1].w, cv = a[n-1].v;
    if(cw<=w)
    {
        int r = cv + Knapsack1(n-1,w-cw);
        if(r > T1[n][w])
        {
            T1[n][w] = r;
        }
    }
    return T1[n][w];
}
int ComputeKnapsack1(int N, int W)
{
    for(int i=0; i<1001; i++)
    {
        for(int j=0; j<31; j++)
        {
            T1[i][j]=-1;
        }
    }
    return Knapsack1(N,W);
}// Recursive - memoization - initialize T then call Knapsack1(N,W);


int T2[1001][31];
int ComputeKnapsack2(int N, int W)
{
    for(int n = 0; n <= N; n++)
    {
        for(int w = 0; w <= W; w++)
        {
            if(n==0)
            {
                T2[n][w] = 0;
                continue;
            }
            T2[n][w] = T2[n-1][w];
            int cw = a[n-1].w, cv = a[n-1].v;
            if(cw <= w)
            {
                int r = cv + T2[n-1][w-cw];
                if(r > T2[n][w])
                {
                    T2[n][w] = r;
                }
            }
        }
    }
    return T2[N][W];
} // Bottom-up, do not save space


int T3[2][31];
int ComputeKnapsack3(int N, int W)
{
    int cur = 0;
    for(int n = 0; n <= N; n++)
    {
        for(int w = 0; w <= W; w++)
        {
            if(n==0)
            {
                T3[cur][w] = 0;
                continue;
            }
            T3[cur][w] = T3[1-cur][w];
            int cw = a[n-1].w, cv = a[n-1].v;
            if(cw <= w)
            {
                int r = cv + T3[1 - cur][w-cw];
                if(r > T3[cur][w])
                {
                    T3[cur][w] = r;
                }
            }
        }
        cur = 1 - cur;
    }
    return T3[1 - cur][W];

} // Bottom-up, use two rows only


int T4[31];
int ComputeKnapsack4(int N, int W)
{
    for (int n = 0; n <= N; n++)
    {
        for (int w = W; w >= 0; w--)
        {
            if(n == 0)
            {
                T4[w] = 0;
                continue;
            }
            int cw = a[n-1].w , cv = a[n-1].v;
            if(cw <= w)
            {
                int r = cv + T4[w - cw];
                if(r > T4[w])
                {
                    T4[w] = r;
                }
            }
        }
    }
    return T4[W];
} // Bottom-up, save maximum space


int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
	return ComputeKnapsack4(N,W);
}

void Compute()
{
    int numberOfTestCases, numberOfPairs,numberOfPeople, result,maxWeight;
    cin>>numberOfTestCases;
    while(numberOfTestCases)
    {
        cin>>numberOfPairs;
        for (int i = 0; i < numberOfPairs; i++)
        {
            cin>>a[i].v>>a[i].w;
        }
        cin>>numberOfPeople;
        result = 0;
        while(numberOfPeople)
        {
            cin>>maxWeight;
            result += ComputeKnapsack(numberOfPairs, maxWeight);
            numberOfPeople--;
        }
        cout<< result <<endl;
        numberOfTestCases--;
    }
} // Get input and call ComputeKnapsack() whenever needed

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "w", stdout);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
