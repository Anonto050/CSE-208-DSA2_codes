#include<bits/stdc++.h>

using namespace std;

struct node
{
    int to,weight;
};

class Graph
{
public:
    vector<node> edge[50000];
    int V;

    Graph(int V)
    {
        this->V = V;
    }

    void addEdge(int u,int v,int w)
    {
        edge[u].push_back({v,w});
    }

    void bfs(int s)
    {
        int dist[V];
        for(int i=0; i<V; i++)
            dist[i]=INT_MAX;

        dist[s] = 0;
        deque<int> q;
        q.push_back(s);

        while (!q.empty())
        {
            int v = q.front();
            q.pop_front();

            for (int i=0; i<edge[v].size(); i++)
            {

                if (dist[edge[v][i].to] > dist[v] + edge[v][i].weight)
                {
                    dist[edge[v][i].to] = dist[v] + edge[v][i].weight;

                    if (edge[v][i].weight == 0)
                        q.push_front(edge[v][i].to);
                    else
                        q.push_back(edge[v][i].to);
                }
            }
        }
        cout<<dist[V-1]<<endl;
    }
};

int main()
{
    int t;
    cin>>t;

    while(t--)
    {
        int n;
        cin>>n;
        Graph g(n);
        int x;

        for(int i=0; i<n; i++)
        {
            cin>>x;
            g.addEdge(i,x-1,0);

            if(x-1!=i+1 && i+1<n)
                g.addEdge(i,i+1,1);
            if(x-1!=i-1 && i>0)
                g.addEdge(i,i-1,1);
        }
        g.bfs(0);
    }
}
