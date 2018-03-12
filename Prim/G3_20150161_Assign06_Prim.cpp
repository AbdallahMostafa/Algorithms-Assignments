// GROUP:   3
// ID:      20150161
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <math.h>
#include <iomanip>
#include<limits.h>

using namespace std;

template<class Value>
struct Array
{
	int n,sz;
    Value* arr;
    void Initialize()
    {
        sz = 1; //size of array
        n = 0; //number of elements
        arr = new Value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(Value v)
    {
        if(n == sz)
        {
            sz*=2;
            Value * new_arr = new Value[sz];
            for(int i =0; i<n; i++)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = nullptr;
            arr = new_arr;
        }
        arr[n++] = v;
    }
    void RemoveLast()
    {
        n--;
    }
    Value& operator[](int i)
    {
        return arr[i];
    }
};



struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};

struct Node
{
	double x,y; // x and y coordinates of the node
	Array<Edge> adj;

	void Initialize()
	{
	    adj.Initialize();
	}
	void Destroy()
	{
	    adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for(int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
    }
    void Destroy()
    {
        for(int i = 0; i < n; i++)
        {
            nodes[i].Destroy();
        }
        delete [] nodes;
        nodes = nullptr;
    }
};

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double  start = 0,end = v,mid;
    for(int i = 0; i <n; i++)
    {
        mid=(start+end)/2.0;
        if((mid*mid) == v) return mid;
        else if(mid*mid > v) end = mid;
        else start = mid;
    }
    return mid;
}
int main()
{
       int numberOfNodes,counter=1;
       Graph graph;
       Array<double> cost;
       Array<int> pervious;
       Array<bool> spanningTree;
       cin>>numberOfNodes;
       while(numberOfNodes != 0)
       {
            graph.Initialize(numberOfNodes);
            for(int i = 0; i < numberOfNodes; i++)
            {
                cin>>graph.nodes[i].x>>graph.nodes[i].y;
            }
            for(int i = 0; i < numberOfNodes; i++)
            {
                for(int j = 0; j <numberOfNodes; j++)
                {
                    Edge edge;
                    edge.v = j;
                    double dx = graph.nodes[j].x - graph.nodes[i].x;
                    double dy = graph.nodes[j].y - graph.nodes[i].y;
                    dx = dx * dx;
                    dy = dy * dy;
                    edge.w = Sqrt(dx+dy);
                    graph.nodes[i].adj.AddLast(edge);
                }
            }
            cost.Initialize();
            pervious.Initialize();
            spanningTree.Initialize();
            for(int  i = 0; i < numberOfNodes;i++)
            {
                spanningTree.AddLast(false);
                cost.AddLast(graph.nodes[0].adj[i].w);
                pervious.AddLast(0);
            }
            cost[0] = 0;
            pervious [0] = -1;
            for(int i = 0; i < numberOfNodes; i++)
            {
                double minimum = INT_MAX;
                int index = 0;

                for(int j = 0; j < numberOfNodes; j++)
                {
                    if(!spanningTree[j] && cost[j] < minimum)
                    {
                        minimum = cost[j];
                        index = j;
                    }
                }
                spanningTree[index] = true;
                for(int j = 0; j < numberOfNodes; j++)
                {
                    if(!spanningTree[j] && graph.nodes[index].adj[j].w < cost[j])
                    {
                        pervious[j] = index;
                        cost[j] = graph.nodes[index].adj[j].w;
                    }
                }
                if(index == 1)
                    break;
            }
            double maximum = -1;
            int index = 1;
            while(pervious[index] != -1)
            {
                if(cost[index] > maximum)
                {
                    maximum = cost[index];
                }
                index = pervious[index];
            }
            cost.Destroy();
            pervious.Destroy();
            spanningTree.Destroy();
            graph.Destroy();
            cout<<"Scenario #"<<counter++<<endl;
            cout<<"Frog Distance = "<<fixed<<setprecision(3)<<maximum<<endl<<endl;
            cin>>numberOfNodes;
       }
	return 0;
}
