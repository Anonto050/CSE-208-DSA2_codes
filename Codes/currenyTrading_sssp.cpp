#include<bits/stdc++.h>

using namespace std;

struct Edge
{
    int u;
    int v;
    double w;
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
        vector<double> key(V,INT_MAX);
        vector<int> parent(V,-1);

        int src = s;

        key[src] = 0;

        for(int j = 1; j<V; j++)
        {
            for(int k = 0; k<E ; k++)
            {
                int x = edge[k].u;
                int y = edge[k].v;
                double weight = edge[k].w;

                if(key[x]!=INT_MAX && key[y]>weight+key[x])
                //if(key[y]>weight+key[x])
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
            double weight = edge[k].w;

            if(key[x]!=INT_MAX && key[y]>weight+key[x])
            //if(key[y]>weight+key[x])
                {
                    flag = true;
                    break;
                }
        }

        if(flag)
            cout<<"There is an anomaly"<<endl;
        else
        {
            cout<<"There are no anomalies"<<endl;

            cout<<"Best exchange rate : "<<pow(10,-key[d])<<endl;

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
    double w;

    cin>>V>>E;
    Graph g(V,E);

    for(int i=0; i<E; i++)
    {
        cin>>u>>v>>w;
        g.addEdge(i,u,v,-1*log10(w));
    }

    cin>>s>>d;
    g.bellman_ford(s,d);
}



