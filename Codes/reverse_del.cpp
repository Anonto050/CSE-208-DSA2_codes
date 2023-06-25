
#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

class Graph
{
    int V;
    list<int> *adj;
    vector< pair<int, Pair>> edges;

public:

    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }


    void addEdge(int u, int v, int w)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({w, {u, v}});
    }

    void DFS(int v, bool visited[])
    {

    visited[v] = true;

    list<int>::iterator i;

    for (i = adj[v].begin(); i != adj[v].end(); i++)
        if (!visited[*i])
            DFS(*i, visited);
}

    bool isConnected()
    {
        bool visited[V];

        for(int i =0;i<V;i++)
        {
            visited[i] = false;
        }

        DFS(0, visited);

        for (int i=1; i<V; i++)
            if (visited[i] == false)
                return false;

        return true;
    }

    void reverseDel_mst()
    {
        sort(edges.begin(), edges.end());

        int weight = 0;

        cout << "Edges in MST\n";

        for (int i=edges.size()-1; i>=0; i--)
        {
            int u = edges[i].second.first;
            int v = edges[i].second.second;

            adj[u].remove(v);
            adj[v].remove(u);

            if (isConnected() == false)
            {
                adj[u].push_back(v);
                adj[v].push_back(u);

                cout << "("<< u << "," << v << ")\n";
                weight += edges[i].first;
            }
        }

        cout <<endl<<"Total weight of MST is " << weight;
    }
};


int main()
{
    int u,v,w,E,V;
    cin>>V>>E;
    Graph g(V);

    for(int i=0; i<E; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }

    cout<<endl;
    g.reverseDel_mst();
    return 0;
}
