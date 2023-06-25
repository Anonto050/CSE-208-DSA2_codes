#include<bits/stdc++.h>

using namespace std;

int graph[10000][10000];

void floyd_warshall(int V,int q)
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

    int m,n;
    for(int i=0; i<q; i++)
    {
        cin>>m>>n;
        if(dp[m-1][n-1]==INT_MAX)
            cout<<"-1"<<endl;
        else
            cout<<dp[m-1][n-1]<<endl;
    }
}

int main()
{

    int u,v,q,m,n;
    int E,V;
    double w;

    cin>>V>>E>>q;

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
        graph[v-1][u-1] = w;
    }

    floyd_warshall(V,q);

}

