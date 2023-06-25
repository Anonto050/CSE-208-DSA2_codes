#include<bits/stdc++.h>

using namespace std;

int graph[10000][10000];

void Matrix_multiplication(int V)
{
    int l[V][V];

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            l[i][j] = graph[i][j];
        }
    }

    for(int m = 1; m < V-1; m++)
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                for(int k=0; k<V; k++)
                {
                    if(l[i][k]!= INT_MAX && graph[k][j] != INT_MAX)
                        l[i][j] = min(l[i][j],l[i][k]+graph[k][j]);
                }
            }
        }
    }

    cout<<"Shortest distance matrix"<<endl;

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            if(l[i][j]==INT_MAX)
                cout<<"INF"<<" ";
            else
                cout<<l[i][j]<<" ";

        }
        cout<<endl;
    }
}

int main()
{

    int u,v;
    int E,V;
    double w;

    cin>>V>>E;

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            if(i==j)
                graph[i][j] = 0;
            else
                graph[i][j] = INT_MAX;
        }
    }

    for(int i=0; i<E; i++)
    {
        cin>>u>>v>>w;
        graph[u-1][v-1] = w;
    }
    Matrix_multiplication(V);

}

