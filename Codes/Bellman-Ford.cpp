#include<bits/stdc++.h>

using namespace std;

struct Edge
{
    int u;
    int v;
    float w;
};

class Graph
{
public:

    int V,E;
    struct Edge* edge;

    Graph(int V,int E)
    {
        this->V = V;
        this->E = E;
        edge = new Edge[E];
    }

    void addEdge(int i,int x,int y,float w)
    {
        edge[i].u = x;
        edge[i].v = y;
        edge[i].w = w;
    }

    void bellman_ford(int s,int d)
    {
        vector<float> key(V,INT_MAX);
        vector<int> parent(V,-1);

        int src = s;

        key[src] = 0;

        for(int j = 1; j<V; j++)
        {
            for(int k = 0; k<E ; k++)
            {
                int x = edge[k].u;
                int y = edge[k].v;
                float weight = edge[k].w;

                //if(key[x]!=INT_MAX && key[y]>weight+key[x])
                if(key[y]>weight+key[x])
                {
                    key[y] = weight+key[x];
                    parent[y] = x;
                }
            }
        }

        bool flag = false;
        for(int k = 0; k<E ; k++)
        {
            int x = edge[k].u;
            int y = edge[k].v;
            float weight = edge[k].w;

            //if(key[x]!=INT_MAX && key[y]>weight+key[x])
            if(key[y]>weight+key[x])
                {
                    flag = true;
                    break;
                }
        }

        if(flag)
            cout<<"The graph contains a negative cycle"<<endl;
        else
        {
            cout<<"The graph does not contain a negative cycle"<<endl;

            cout<<"Shortest path cost : "<<key[d]<<endl;

            stack<int> sssp;

            int i = d;
            while(i!=s)
            {
                sssp.push(i);
                i=parent[i];
            }
            sssp.push(s);

            int cnt = 0;
            while(!sssp.empty())
            {
                if(cnt>0)
                    cout<<"->";
                cout<<sssp.top();
                sssp.pop();
                cnt++;
            }
        }
    }

};

int main()
{

    int u,v,E,V,s,d;
    float w;

    cin>>V>>E;
    Graph g(V,E);

    for(int i=0; i<E; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(i,u,v,w);
    }

    cin>>s>>d;
    g.bellman_ford(s,d);
}


