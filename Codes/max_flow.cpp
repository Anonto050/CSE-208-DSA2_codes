#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

int graph[1000][1000];
int g[1000][1000];
int rGraph[1000][1000];
int w[10000],r[10000],l[10000];
string str[100000];

bool bfs(int V, int s, int t, int parent[])
{
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				if (v == t) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return false;
}

bool fordFulkerson(int V, int s, int t)
{
	int u, v;
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++){
			rGraph[u][v] = graph[u][v];
		}

	int parent[V];

	int max_flow = 0;

	while (bfs(V, s, t, parent)) {

		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

    for(int i=1;i<=V*(V-1)/2;i++)
     {
          cout<<rGraph[s][i]<<endl;
         if(rGraph[s][i]!=0)
         {
             //return true;
         }
     }
	return false;
}

void baseBAll_elmn(int n,int x)
{

  int y = 1+(n*(n-1))/2 ;
  int s = 0;
  int t = y+n;
  int c =1;

    for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++)
    {
        if(i==x || j==x)
        {
            c++;
            continue;
        }
        graph[s][c] = g[i][j];
        graph[c][y+i] = INT_MAX;
        graph[c][y+j] = INT_MAX;
        c++;
    }
 }

 for(int i=0;i<n;i++)
 {
     if(i == x)
        continue;
     graph[y+i][t] = w[x]+r[x]-w[i];
 }

	if(fordFulkerson(t+1, s, t))
        cout<<str[x]<<" is Eliminated"<<endl;


}

int main()
{
	 int n;
  cin>>n;

  //string str[n];
  //int g[n][n];
  //int w[n],l[n],r[n];

  for(int i=0;i<n;i++)
  {
      cin>>str[i];
      cin>>w[i]>>l[i]>>r[i];
      for(int j=0;j<n;j++)
      {
          cin>>g[i][j];
      }
  }
for(int x = 0;x<n;x++)
    baseBAll_elmn(n,x);
}

