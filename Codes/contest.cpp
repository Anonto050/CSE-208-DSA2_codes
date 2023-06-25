#include<bits/stdc++.h>

using namespace std;

class Graph
{
public:
    long long int V;
    vector<list<long long int>> adj;

    Graph(long long int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(long long int u,long long int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void BFS( )
    {
        vector<bool> visited;
        vector<int> wt;
        long long int sum=0;
        wt.resize(V);

        for(long long int i=0; i<V; i++)
            {
                wt[i]=0;
            }

        visited.resize(V,false);

        for(long long int i=0; i<V; i++)
        {
            if(!visited[i])
            {
                for(auto adjecent : adj[i])
                {
                        visited[adjecent] = true;
                        wt[i]++;
                }
                visited[i]=true;
            }
        }
        for(long long int i=0; i<V; i++){
                //cout<<wt[i]<<endl;
            sum = sum+wt[i];
        }
        if(sum>(V-sum))
           cout<<sum<<endl;
           else
            cout<<V-sum<<endl;
    }

};

int main()
{

    long int t,cnt=1;
    cin>>t;
    while(t--)
    {

        long long int n,u,v;
        cin>>n;

        Graph g(n+1);

        for(long long int i=0; i<n; i++)
        {
            cin>>u>>v;
            g.addEdge(u-1,v-1);
        }
        cout<<"Case "<<cnt<<": ";
        cnt++;
        g.BFS();
    }

}

