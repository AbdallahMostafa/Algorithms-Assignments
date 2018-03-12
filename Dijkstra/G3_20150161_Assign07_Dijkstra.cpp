// GROUP:   3
// ID:      20150161
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Abdallah Mostafa
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits.h>
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

template<class Elem>
struct Heap
{
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) // n is required to allocate and initialize pos[]
    {
        a.Initialize();
        pos = new int[n];
        for (int i = 0; i <n; i++)
        {
            pos[i] = -1;
        }
        this->IsBefore = _IsBefore;
    }
    void Destroy()
    {
        a.Destroy();
        delete [] pos;
    }
    //void Print();
    int Child(int i)
    {
        return (2*i)+1;
    }

    int Parent(int i)
    {
        return (i-1)/2;
    }

    Elem GetFirst()
    {
        return a[0];
    }

    Elem RetrieveFirst()
    {
        //3a4an atb3o
        Elem tempway = a[0];
        a[0] = a[a.n-1];
        pos[a[a.n-1].v] = -1;
        pos[a[0].v] = 0;
        a.RemoveLast();
        MoveDown(0);
        return tempway;
    }

    void Add(Elem e)
    {
        a.AddLast(e);
        pos[e.v] = a.n-1;
        MoveUp(a.n-1);
    }

    void MoveUp(int ind)
    {
        int temp = ind;
        if(ind == 0)
        {
            pos[a[ind].v] = ind ;
            return ;
        }
        while(IsBefore(a[temp], a[Parent(temp)]))
        {
            //swap in position
            pos[a[temp].v] = Parent(temp);
            pos[a[Parent(temp)].v] = temp;

            Elem tempway = a[temp];
            a[temp] = a[Parent(temp)];
            a[Parent(temp)] = tempway;
            temp = Parent(temp);

        }
    }

    void MoveDown(int ind)
    {
        int temp = ind;
        bool check = false;

        while (Child(temp) < a.n || (Child(temp)+1) < a.n)
        {
            check = false;
            if(Child(temp)+1 < a.n)
            {
                if(IsBefore(a[Child(temp)], a[Child(temp)+1]))
                {
                    if (IsBefore(a[Child(temp)], a[temp]))
                    {
                        //swap in position
                        pos[a[temp].v]= Child(temp);
                        pos[a[Child(temp)].v] = temp;


                        Elem tempway = a[temp];
                        a[temp] = a[Child(temp)];
                        temp = Child(temp);
                        check = true;
                        a[temp]=tempway;
                    }
                }
                else if (IsBefore(a[Child(temp)+1], a[temp]))
                {
                    pos[a[temp].v]= Child(temp);
                    pos[a[Child(temp)].v] = temp;

                    Elem tempway = a[temp];
                    a[temp] = a[Child(temp)+1];
                    temp = Child(temp)+1;
                    check = true;
                    a[temp] = tempway;
                }
            }
            else
            {
                if(IsBefore(a[Child(temp)], a[temp]))
                {
                    pos[a[temp].v]= Child(temp);
                    pos[a[Child(temp)].v] = temp;

                    Elem tempway = a[temp];
                    a[temp] = a[Child(temp)];
                    temp = Child(temp);
                    check = true;
                    a[temp]=tempway;
                }
            }
            if(!check)
            {
                break;
            }
        }
    }
};

struct Edge
{
    int		v;
    int		w;
};

struct Node
{
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
        n=_n;
        nodes = new Node[n];
        for(int i=0; i<n; i++)
        {
            nodes[i].Initialize();
        }
    }
    void Destroy()
    {
        for(int i=0; i<n; i++)
        {
            nodes[i].Destroy();
        }
        delete [] nodes;
        nodes = nullptr;
    }
};

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

int main()
{
    int testCases,n,m,s,t;
    Graph graph;
    Heap<Edge> heap;
    Array<int> cost;
    cin>>testCases;
    for(int _i = 0; _i < testCases; _i++)
    {
        cin>>n>>m>>s>>t;
        graph.Initialize(n);
        for(int j = 0; j < m; j++)
        {
            Edge edge;
            int v,u,w;
            cin>>v>>u>>w;
            edge.v = u;
            edge.w = w;
            graph.nodes[v].adj.AddLast(edge);
            edge.v = v;
            graph.nodes[u].adj.AddLast(edge);
        }
        cost.Initialize();
        heap.Initialize(IsBefore,m);
        for(int i = 0; i < n; i++)
            cost.AddLast(INT_MAX);
        for(int i = 0; i <graph.nodes[s].adj.n; i++)
        {
            heap.Add(graph.nodes[s].adj[i]);
            cost[graph.nodes[s].adj[i].v] = graph.nodes[s].adj[i].w;
        }
        Edge tempway;
        while(heap.a.n)
        {
            tempway = heap.RetrieveFirst();
            s = tempway.v;
            for(int i = 0; i < graph.nodes[s].adj.n; i++)
            {
                int value = graph.nodes[s].adj[i].v, weight = graph.nodes[s].adj[i].w;
                if(cost[s] + weight < cost[value])
                {

                    cost[value] = cost[s]+weight;
                    heap.Add(graph.nodes[s].adj[i]);
                }
            }
        }
        if(cost[t]== INT_MAX)
        {
            cout<<"Case #"<<_i+1<<": unreachable"<<endl;
        }else
        {
            cout<<"Case #"<<_i+1<<": "<<cost[t]<<endl;
        }
        cost.Destroy();
        heap.Destroy();
        graph.Destroy();
    }
    return 0;
}
