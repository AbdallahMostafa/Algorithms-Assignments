// GROUP:   3
// ID:      20150161
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i = 0, j = mid, k;
    Type *t = new Type[n];
    for(k = 0; k < n; k++) //o(n)
    {
        if(j==n || (i < mid && IsBefore(a[i], a[j])))
        {
            t[k] = a[i++];
        }
        else
        {
            t[k] = a[j++];
        }
    }
    for(int i = 0; i < n; i++)
    {
        a[i] = t[i];
    }
    delete [] t;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if(n<=1)
    {
        return;
    }
    MergeSort<Type>(a, mid, IsBefore);
    MergeSort<Type>(a+mid, n-mid, IsBefore);
    Merge<Type>(a, n, IsBefore);
}

struct Obj
{
    int v;
    int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

bool IsBefore(Obj& a, Obj& b)
{
    return ((double)a.v/a.w) > ((double)b.v/b.w);
} // return true if unit value of a is greater than unit value of b

int best_val; // the best total value found until now

int Bound(int i, int w)
{
    int sum = 0;
    int initweight=w;
    for (int j = i; j < n; j++)
    {
        if(a[j].w <= initweight)
        {
            sum += a[j].v;
            initweight -= a[j].w;
        }
        else
        {
            sum += ((double)a[j].v / (double)a[j].w) * initweight;
            return sum;
        }
    }
} // upper bound on the total value of items [i..n-1] that can fit in w

void BackTrack(int i, int w, int cur_val)
{
    if(i == n)
    {
        if(best_val < cur_val)
        {
            best_val = cur_val;
        }
        return;
    }
    int functionCallResult = Bound(i, w);
    if(functionCallResult + cur_val < best_val)
    {
        return;
    }
    if(w >= a[i].w)
    {
        BackTrack(i+1, w - a[i].w, cur_val + a[i].v);
    }
    BackTrack(i+1,w,cur_val);

} // starting from item i, remaining weight w, cur_value of objects[0..i-1]

int ComputeKnapsack(int N, int W)
{
    best_val = 0;
} // solve knapsack of N objects and W weight

void Compute()
{
    int testCase, sum, numberOfPeoplePerGroup,weight;
    cin>>testCase;
    best_val=0;
    while(testCase--)
    {
        cin>>n;
        sum = 0;
        for(int i = 0; i < n; i++)
        {
            cin>>a[i].v >> a[i].w;
        }
        MergeSort(a, n, IsBefore);
        cin>>numberOfPeoplePerGroup;
        for(int j = 0; j < numberOfPeoplePerGroup; j++)
        {
            cin>>weight;
            BackTrack(0,weight,0);
            sum += best_val;
            best_val = 0;
        }
        cout<<sum<<endl;
    }
}
int main()
{
    //freopen("input_assign12_10130.txt", "w", stdout);
    Compute();
    return 0;
}
