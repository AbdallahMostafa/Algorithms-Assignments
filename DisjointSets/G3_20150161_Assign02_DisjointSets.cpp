// GROUP:   3
// ID:      20150161
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
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


int main()
{
    int test,num_citizen,num_relations,tempway1 , tempway2,holdway = 1;
    DisjointSets disjoinsets;
    cin>>test;
    while(test--)
    {
        cin>>num_citizen>>num_relations;
        disjoinsets.Initialize(num_citizen);
        for(int i = 0; i < num_relations; i++)
        {
            cin>>tempway1>>tempway2;
            disjoinsets.Union(tempway1-1 , tempway2-1);
        }
        holdway = 1;
        for(int i = 0; i<disjoinsets.n ; i++)
        {
            if(holdway < disjoinsets.num_nodes[i])
                holdway = disjoinsets.num_nodes[i];
        }
        cout <<holdway<<endl;
        disjoinsets.Destroy();
    }
	return 0;
}

