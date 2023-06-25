#include<bits/stdc++.h>

using namespace std;

class Graph
{
public:

    int V;
    list<pair<float,int>> *adj;

    Graph(int V)
    {
        this->V = V;
        adj = new list<pair<float,int>>[V];
    }

    void addEdge(int x,int y,float w)
    {
        adj[x].push_back(make_pair(w,y));
    }

    void dijkstra(int s,int d,float cost)
    {
        priority_queue< pair<float,int>,vector<pair<float,int>>,greater<pair<float,int>> > pq;

        vector<float> key(V,INT_MAX);
        vector<int> parent(V,-1);
        vector<bool> visited(V,false);

        int src = s;

        key[src] = cost;
        pq.push(make_pair(cost,src));

        while(!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if(visited[u]==true)
                continue;
            visited[u] = true;

            list<pair<float,int>> :: iterator i;

            for(i = adj[u].begin(); i != adj[u].end(); i++)
            {
                int v = (*i).second;
                float weight = (*i).first;

                if(visited[v]==false && key[v]>weight+key[u])
                {
                    key[v] = weight+key[u];
                    pq.push(make_pair(key[v],v));
                    parent[v] = u;
                }
            }

        }

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

};

int main(){

  int u,v,E,V,s,d;
  float w,c;


  cin>>V>>E;
  Graph g(V);
  float cost[V];

  for(int i=0;i<V;i++){
    cin>>u>>c;
    cost[u] = c;
  }

  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    g.addEdge(u,v,w+cost[v]);
  }

  cin>>s>>d;
  g.dijkstra(s,d,cost[s]);
}


