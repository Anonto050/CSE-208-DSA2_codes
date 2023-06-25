#include<bits/stdc++.h>

using namespace std;

int main(){

  int n;
  cin>>n;

  string str[n];
  int g[n][n];
  int graph[n][n];
  int w[n],l[n],r[n];

  for(int i=0;i<n;i++)
  {
      cin>>str[i];
      cin>>w[i]>>l[i]>>r[i];
      for(int j=0;j<n;j++)
      {
          cin>>g[i][j];
      }
  }
  for(int i=0;i<n;i++)
  {
      cout<<str[i]<<endl;
      cout<<w[i]<<" "<<l[i]<<" "<<r[i]<<endl;
      for(int j=0;j<n;j++)
      {
          cout<<g[i][j]<<" ";
      }
      cout<<endl;
  }

  int y = n(n-1)/2 ;
  int s = y+n;
  int t = s+1;

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

}
