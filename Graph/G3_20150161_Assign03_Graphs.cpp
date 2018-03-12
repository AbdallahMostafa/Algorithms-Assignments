// GROUP:   G3
// ID:      20150161
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Abdallah Mostafa Mokhtar
// Handle:  abdallah_mostafa
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


template<class Value>
struct Array
{
    int n, sz;
    Value* arr;
    void Initialize()
    {
        sz = 1;
        n = 0;
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
            for(int i =0; i < n; i++)
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


struct Node
{
    Array<int> adj;//neighbors

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
    Node* nodes; //graph

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


template <class Type>
struct Queue
{
    int f, n;//f = first index , n = the first empty element
    Type* elems;

    void Initialize(int size)
    {
        n = 0;
        f = 0;
        elems = new Type[size];
    }
    void Destroy()
    {
        delete [] elems;
    }
    void Add(Type t)
    {
        elems[n++] = t;
    }
    Type Pop()
    {
        Type t = elems[f];
        f++;
        return t;
    }
    Type Peek()
    {
        return elems[f];
    }
    int Num()
    {
        return n-f;
    }
};

int main()
{
    int num_people,relation,relway,test ,start, hold = 0;
    Graph graph;
    Queue <int> q;
    cin>>num_people;
    graph.Initialize(num_people);
    bool * visited = new bool[num_people];
    int * days = new int[num_people];
    int * dis = new int[num_people];
    for(int i = 0; i <num_people; i++)
    {
        cin>>relation;
        for(int j = 0; j < relation; j++)
        {
            cin>>relway;
            graph.nodes[i].adj.AddLast(relway);
        }
    }
    cin>>test;
    while(test--)
    {
        for(int i = 0; i<num_people; i++)
        {
            visited[i] = false;
            days[i] = 0;
            dis[i] = 0;
        }
        q.Initialize(num_people);
        cin>>start;
        q.Add(start);
        visited[start] = true;
        while(q.Num())
        {
            int popway = q.Pop();
            for(int i = 0; i<graph.nodes[popway].adj.n; i++)
            {
                if(!visited[graph.nodes[popway].adj[i]])
                {
                    q.Add(graph.nodes[popway].adj[i]);
                    visited[graph.nodes[popway].adj[i]] = true;
                    dis[graph.nodes[popway].adj[i]] = 1+ dis[popway];
                }
            }
        }
        for(int i = 0; i < num_people; i++)
        {
            if(dis[i]!=0)
            {
		//dis[5] = 3
		//dis[2] = 3
		//days[dis[5]] = days[3]
		//days[dis[2]] = days[3]
		//days[index] = 2
		//yeb2a fe etnen 3rfoo
                days[dis[i]]++;
            }
        }
        hold = 0;
        for(int i = 1; i < num_people; i++)
        {

            if(days[hold]<days[i])
            {
                hold = i;
            }
        }
        if(hold)
	{
            cout<<days[hold]<<" "<<hold<<endl ;
        }
        else
	{
            cout<<0<<endl;
        }
    }
    return 0;
}
