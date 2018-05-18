// GROUP:   3
// ID:      20150161
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Abdallah Mostafa
// UVA Username: abdallah_mostafa

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
#include <iomanip>
#include <limits>

#define INT_MAX 214743647;

using namespace std;

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

#define MAX_COMPUTERS 8

struct Point
{
    int x,y;
};
double Dist(Point& a, Point& b)
{
    double x1, x2, y1, y2, x1_x2, y1_y2, x_x, y_y;
    x1 = a.x;
    x2 = b.x;
    y1 = a.y;
    y2 = b.y;
    x1_x2 = x2 - x1;
    y1_y2 = y2 - y1;
    x_x = x1_x2 * x1_x2;
    y_y = y1_y2 * y1_y2;
    return sqrt(x_x + y_y);
}

int		n; // number of computers (input)
Point	com[MAX_COMPUTERS]; // locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)

double	best_val; // best value until now
int		best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.

void UpdateSol()
{
    double tempValue = 0;
    for(int i=1; i<n; i++)
    {
        tempValue += dist[s[i-1]][s[i]];
    }
    if(tempValue < best_val)
    {
        best_val = tempValue;
        for(int i=0; i<n; i++)
        {
            best_sol[i] = s[i];
        }
    }
} // evaluate the permutation s, then update best_val and best_sol if necessary


void Backtrack0(int i)
{
    if (i == n)
    {
        UpdateSol();
        return;
    }
    for (int j = i; j < n; j++)
    {
        cout<<i<<"-----"<<j<<endl;
        swap(s[i], s[j]);
        Backtrack0(i+1);
        swap(s[i], s[j]);
    }
} // backtrack using swaps
void Compute0()
{
    for (int i = 0; i < n; i++)
    {
        best_sol[i] = -1;
    }
    Backtrack0(0);
} // do necessay initializations and call Backtrack0()


bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation

void Backtrack1(int i)
{
    if (i == n)
    {
        UpdateSol();
        return;
    }
    for (int  j = 0; j < n; j++)
    {
        if(!v[j])
        {
            s[i] = j;
            v[j] = true;
            Backtrack1(i+1);
            v[j] = false;
        }
    }
} // backtrack using the v[] array
void Compute1()
{
    for (int i = 0; i < n; i++)
    {
        v[i] = false;
        best_sol[i] = -1;
    }
    Backtrack1(0);
} // do necessay initializations and call Backtrack1()

// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i)
{
    F[B[i]]=F[i];
    B[F[i]]=B[i];
}
void Restore(int i)
{
    B[F[i]]=i;
    F[B[i]]=i;
}
void InitDancingLinks(int n)
{
    int i;
    for(i=0; i<n; i++) F[i]=i+1;
    F[n]=0;
    for(i=n; i>0; i--) B[i]=i-1;
    B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes


void Backtrack2(int i)
{
    if (i == n)
    {
        UpdateSol();
        return;
    }
    for (int j = F[0]; j != 0; j = F[j])
    {
        s[i] = j-1;
        Remove(j);
        Backtrack2(i+1);
        Restore(j);
    }
} // backtrack using dancing links
void Compute2()
{
    for (int i = 0; i < n; i++)
    {
        best_sol[i] = -1;
    }
    InitDancingLinks(n);
    Backtrack2(0);
} // do necessay initializations and call Backtrack2()


void ComputeCore()
{
    // do necessay initializations of dist[][] and best_val
    best_val = INT_MAX;
    for(int i=0; i<n; i++)
    {
        s[i]=i;
        for(int j=0; j<n; j++)
        {
            if(i==j)
            {
                dist[i][j] = 0;
            }
            else
            {
                dist[i][j] = Dist(com[i], com[j]) + 16.0;
                dist[j][i] = dist[i][j];
            }
        }
    }
    //Compute0();
    Compute1();
    //Compute2();
}


void Compute()
{
    int numberOfNetwork = 1;
    cin>>n;
    while(n != 0)
    {
        for(int i = 0; i < n; i++)
        {
            cin>> com[i].x >> com[i].y;
        }
        cout<<"**********************************************************"<<endl;
        cout<<"Network #"<<numberOfNetwork++<<endl;
        ComputeCore();
        for(int i = 1; i < n; i++)
        {
            cout<<"Cable requirement to connect ("<<com[best_sol[i-1]].x<<","<<com[best_sol[i-1]].y <<") to ("<< com[best_sol[i]].x<<","<<com[best_sol[i]].y<<") is "<<fixed<<setprecision(2)<<dist[best_sol[i-1]][best_sol[i]]<<" feet."<<endl;
        }
        cout<<"Number of feet of cable required is "<<fixed<<setprecision(2)<<best_val<<"."<<endl;

        cin>>n;
    }
} // get input and then call ComputeCore(); then print output


int main()
{
    //freopen("input_assign13_00216.txt", "r", stdin);
    Compute();
    return 0;
}
