#include<bits/stdc++.h>

using namespace std;

int graph[10000][10000];

void floyd_warshall(int V)
{
    int dp[V][V];

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            dp[i][j] = graph[i][j];
        }
    }

    for(int k=0; k<V; k++)
    {
        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                  if(dp[i][k]==INT_MAX || dp[k][j]==INT_MAX)
                    continue;
                  if(dp[i][k]+dp[k][j]<dp[i][j])
                    dp[i][j] = dp[i][k]+dp[k][j];
            }
        }
    }

    cout<<"Shortest distance matrix"<<endl;

    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            if(dp[i][j]==INT_MAX)
               cout<<"INF"<<" ";
            else
                cout<<dp[i][j]<<" ";

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

    //int graph[V][V];

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
    floyd_warshall(V);

}
