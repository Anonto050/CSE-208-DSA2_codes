import java.io.*;
import java.util.*;

class Graph_cyclicUndirected
{
    private int V;

    // Adjacency List Representation
    private LinkedList<Integer> adj[];

    // Constructor
    Graph_cyclicUndirected(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for(int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }

    void addEdge(int v,int w)
    {
        adj[v].add(w);
        adj[w].add(v);
    }

    Boolean isCyclicUtil(int v, Boolean visited[], int parent)
    {
        // Mark the current node as visited
        visited[v] = true;
        Integer i;

        Iterator<Integer> it = adj[v].iterator();
        while (it.hasNext())
        {
            i = it.next();

            if (!visited[i])
            {
                if (isCyclicUtil(i, visited, v))
                    return true;
            }

            else if (i != parent)
                return true;
        }
        return false;
    }

    Boolean isCyclic()
    {

        Boolean visited[] = new Boolean[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;

        for (int u = 0; u < V; u++)
        {
            if (!visited[u])
                if (isCyclicUtil(u, visited, -1))
                    return true;
        }

        return false;
    }

    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        int V = sc.nextInt();
        int E = sc.nextInt();

        Graph_cyclicUndirected g = new Graph_cyclicUndirected(V);

        for(int i=0;i<E;i++){
            int u = sc.nextInt();
            int v = sc.nextInt();

            g.addEdge(u,v);
        }

        if(g.isCyclic())
            System.out.println("Graph contains cycle");
        else
            System.out.println("Graph does not contain cycle");
    }
}


