// GROUP:   3
// ID:      20150161
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Abdallah Mostafa
// Handle:  abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template <class Type>
Type CountInvMerge(long long* a, int n, bool(*IsBefore)(long long & , long long &))
{
    //cout<<a[0] << " ";
    long long mid = n/2;
    long long i = 0,j = mid, k, val=0;
    Type *t = new Type[n];
    for(k=0;k<n;k++)//o(n)
    {
        if(j==n || (i<mid && IsBefore(a[i],a[j])))
        {
            t[k] = a[i++];
        }else
        {
            val+=mid-i;
            t[k] = a[j++];
        }
    }
    for ( int i = 0; i<n; i++)
    {
        a[i] = t[i];
    }
    delete[] t;
    return val;
}
template <class Type>
Type CountInv(long long* a, int n, bool(*IsBefore)(long long & , long long &))
{
    long long x , b ,c;
    long long mid = n/2;
    if(n<=1)
    {
        return 0;
    }
    x = CountInv<Type>(a, mid, IsBefore);
    b = CountInv<Type>(a+mid, n-mid, IsBefore);
    c = CountInvMerge<Type>(a, n, IsBefore);
    return x + b + c;
}
bool IsBeforeInt(long long& a, long long& b)
{
    return a<=b;
}
int main()
{
    freopen("test.txt" , "w" ,stdout);
    long long test,element_of_array;
    long long * arr;
    cin>>test;
    while(test!=0)
    {
        arr = new long long[test];
        for(int i = 0; i<test; i++)
        {
            cin>>element_of_array;
            arr[i] = element_of_array;
        }
        cout<<CountInv<long long>(arr, test, IsBeforeInt)<<endl;
//        for ( int i = 0;i < test; i++)
//        {
//            cout<<arr[i]<<" ";
//        }
        delete [] arr;
        cin>>test;
    }
	return 0;
}
