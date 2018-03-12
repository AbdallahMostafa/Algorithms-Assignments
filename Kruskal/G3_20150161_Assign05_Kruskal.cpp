// GROUP:   3
// ID:      20150161
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Abdallah Mostafa Mokhtar
// Handle:  abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;



struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
	{
		n = _n;
		parent = new int[n];
		num_nodes = new int[n];
		for(int i = 0; i <n;i++)
        {
            num_nodes[i] = 1;
            parent[i] = i;
        }
	}
	void Destroy()
	{
		delete [] parent;
		parent = nullptr;
		delete [] num_nodes;
		num_nodes = nullptr;
	}
	int Find(int i)
	{
        while(parent[i] != i)
            i = parent[i];
        return i ;
	}
	bool Union(int i, int j)
	{
        int num1 = Find(i);
        int num2 = Find(j);
        if (num1 == num2)
            return false;
        if(num_nodes[num1] <= num_nodes[num2])
        {
            parent[num1] = num2;
            num_nodes[num2] += num_nodes[num1];
        }
        else
        {
            parent[num2] = num1;
            num_nodes[num1] += num_nodes[num2];
        }
        return true;
	}
};
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    int i = 0,j = mid, k;
    Type *t = new Type[n];
    for(k=0;k<n;k++)//o(n)
    {
        if(j==n || (i<mid && IsBefore(a[i],a[j])))
        {
            t[k] = a[i++];
        }else
        {
            t[k] = a[j++];
        }
    }
    for ( int i = 0; i<n; i++)
    {
        a[i] = t[i];
    }
    delete[] t;
}


template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if(n<=1)
    {
        return ;
    }
    MergeSort<Type>(a, mid, IsBefore);
    MergeSort<Type>(a+mid, n-mid, IsBefore);
    Merge<Type>(a, n, IsBefore);
}
struct Edge
{
	int u, v; // u = point_1 , v = point_2
	int w;
};
bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}
int main()
{
    Edge *edge;
    DisjointSets disjoinset;
    int m , n ,valway = 0;
    cin>>m>>n;
    while(m!=0)
    {
        valway = 0;
        edge = new Edge [n];
        disjoinset.Initialize(m);
        for (int i = 0 ; i < n ; i++)
        {
            cin>>edge[i].u>>edge[i].v>>edge[i].w;
        }
        MergeSort(edge , n , IsBeforeEdge);
        for (int i = 0; i <n; i++)
        {
            if(!disjoinset.Union(edge[i].u,edge[i].v))
            {
                valway+=edge[i].w;
            }
        }
        disjoinset.Destroy();
        delete [] edge;
        cout<<valway<<endl;
        cin>>m >>n;
    }

	return 0;
}


