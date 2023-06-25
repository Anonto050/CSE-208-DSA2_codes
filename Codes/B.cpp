#include<bits/stdc++.h>

using namespace std;

int node[100000];
int a[100000];
int w[100000];

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int> > adj;

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void DFS(int v,int m)
    {
        visited[v] = true;

        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
            if (!visited[*i])
            {
                if(w[*i] != 0 && w[v]!=0)
                    w[*i]++;
                else
                    w[*i]=0;
                if(w[*i]>m)
                    w[*i]=-1;

                DFS(*i,m);
            }


    }
};

int main()
{

    int n,m;
    cin>>n>>m;

    //int a[n];

    Graph g;
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
        w[i] = a[i];
    }

    int u,v;
    for(int i=0; i<n-1; i++)
    {
        cin>>u>>v;
        node[u]=1;
        g.addEdge(u-1,v-1);
    }

    g.DFS(0,m);
    int sum=0;

    for(int i=0; i<n; i++)
    {
        if(node[i]==0)
        {
            if(w[i]==0)
                sum+=1;
        }
    }
    cout<<sum<<endl;

    return 0;
}
