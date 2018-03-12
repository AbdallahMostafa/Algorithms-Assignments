// GROUP:   3
// ID:      20150161
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Abdallah Mostafa Mokhtar
#include <bits/stdc++.h>

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
template <class Elem>
struct Heap
{
    Array<Elem> a;
    bool(*IsBefore)(Elem&,Elem&);
    void Intialize(bool (*_IsBefore)(Elem&, Elem&))
    {
        a.Initialize();
        IsBefore = _IsBefore;
    }
    void Destroy()
    {
        a.Destroy();
    }
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
        a.RemoveLast();
        MoveDown(0);
        return tempway;
    }
    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n-1);
    }
    void MoveUp(int ind)
    {
        int temp = ind;
        if(ind == 0)
        {
            return ;
        }
        while(a[temp] < a[Parent(temp)])
        {
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
                        Elem tempway = a[temp];
                        a[temp] = a[Child(temp)];
                        temp = Child(temp);
                        check = true;
                        a[temp]=tempway;
                    }
                }
                else if (IsBefore(a[Child(temp)+1], a[temp]))
                {
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
    void Print()
    {
        for(int i =0; i < a.n-1; i++)
        {
            cout<<a[i]<<", ";
        }
        cout<<a[a.n-1]<<endl;
    }
};
bool IsBeforeInt(int& a, int& b)
{
    return a<b;
}

int main()
{
    Heap <int>*h = new Heap<int>;
    int limit, temp, input, elem1;
    cin>>limit;
    while(limit)
    {
        h->Intialize(IsBeforeInt);
        temp = 0;
        for(int i = 0; i < limit; i++)
        {
            cin>>input;
            h->Add(input);
        }
        while(h->a.n !=1)
        {
            elem1 = h->RetrieveFirst();
            elem1+= h->RetrieveFirst();
            temp +=elem1;
            h->Add(elem1);
        }
        h->Destroy();
        cout<<temp<<endl;
        cin>>limit;
    }
    return 0;
}
