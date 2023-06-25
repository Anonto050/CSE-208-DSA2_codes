#include<bits/stdc++.h>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class dset
{
    int* parent;
    int* rank;

public:

    dset(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for(int i=0; i<n; i++)
        {
            parent[i] = -1;
            rank[i] = 0;
        }
    }

    int find_set(int i)
    {
        if(parent[i]==-1)
            return i;
        return parent[i]=find_set(parent[i]);
    }

    void union_set(int x,int y)
    {

        int r1,r2;
        r1 = find_set(x);
        r2 = find_set(y);

        if(rank[r1]>rank[r2])
        {
            parent[r2] = r1;
        }
        else if(rank[r1]<rank[r2])
        {
            parent[r1] = r2;
        }
        else
        {
            parent[r1] = r2;
            rank[r2]++;
        }
    }
};

vector<pair<int,int>> krushkal_edge;
vector<pair<int,int>> prim_edge;
float cost;

class Graph_mst
{
public:
    vector<vector<int>> edge;
    int V;

    Graph_mst(int V)
    {
        this->V = V;
    }

    void addEdge(int x,int y,int w)
    {
        edge.push_back({w,x,y});
    }

    float mst_krushkals()
    {
        sort(edge.begin(),edge.end());

        dset dsu(V);
        //float cost = 0;

        for(auto edges : edge)
        {
            float w = edges[0];
            int x = edges[1];
            int y = edges[2];


            if(dsu.find_set(x)!=dsu.find_set(y))
            {
                dsu.union_set(x,y);
                cost += w;
                krushkal_edge.push_back(make_pair(x,y));
            }
        }
        //cout<<cost<<endl;
        //cout<<krushkal_edge.size()<<endl;
        return cost;
    }

    void print_krushkal()
    {
        int n = krushkal_edge.size();
        cout<<"List of edges selected by Krushkal's : {";
        for(int i = 0; i<n; i++)
        {
            cout<<"("<<krushkal_edge[i].first<<","<<krushkal_edge[i].second<<")";
            if(i<n-1)
                cout<<",";
        }
        cout<<"}"<<endl;
    }

};

class Graph_prim
{
public:

    int V;
    list<pair<int,int>> *adj;

    Graph_prim(int V)
    {
        this->V = V;
        adj = new list<pair<int,int>>[V];
    }

    void addEdge(int x,int y,int w)
    {
        adj[x].push_back(make_pair(w,y));
        adj[y].push_back(make_pair(w,x));
    }

    void mst_prim()
    {
        priority_queue< pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > pq;

        vector<int> key(V,INT_MAX);
        vector<int> parent(V,-1);
        vector<bool> visited(V,false);

        int src = 0;
        int cost = 0;

        key[src] = 0;
        pq.push(make_pair(0,src));

        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if(visited[u]==true)
                continue;
            visited[u] = true;

            list<pair<int,int>> :: iterator i;

            for(i = adj[u].begin(); i != adj[u].end(); i++)
            {
                int v = (*i).second;
                int weight = (*i).first;

                if(visited[v]==false && key[v]>weight)
                {
                    key[v] = weight;
                    pq.push(make_pair(key[v],v));
                    parent[v] = u;
                }
            }

        }
             //cout<<cost<<endl;

        cout<<"List of edges selected by Prim's : {";

        for(int i = 1; i < V; i++)
        {
            cout<<"("<<parent[i]<<","<<i<<")";
            if(i<V-1)
                cout<<",";
        }
        cout<<"}"<<endl;
    }

};

int main()
{

    int x,y,E,V;
    float w;

    string line;
    ifstream myfile ("mst.in.txt");

    if (myfile.is_open())
    {
        myfile>>V>>E;


        Graph_mst m(V);
        Graph_prim p(V);

        for(int i = 0; i<E; i++)
        {
            myfile>>x>>y>>w;
            m.addEdge(x,y,w);
            p.addEdge(x,y,w);
        }

        cost = m.mst_krushkals();
        cout<<"Cost of the minimum spanning tree : "<<cost<<endl;

        p.mst_prim();
        m.print_krushkal();

        myfile.close();
    }

    else
        cout << "Unable to open file";

}
