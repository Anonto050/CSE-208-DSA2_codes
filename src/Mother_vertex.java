import java.util.*;

class Graph_motherVertex{

    private int V;

    // Adjacency List Representation
    private LinkedList<Integer> adj[];

    // Constructor
    Graph_motherVertex(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for(int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }

    void addEdge(int v,int w)
    {
        adj[v].add(w);
    }

    void DFSUtil(int v, boolean[] visited)
    {
        visited[v] = true;

        Iterator<Integer> it = adj[v].iterator();
        while (it.hasNext()) {
            int x = it.next();
            if (!visited[x])
                DFSUtil(x, visited);
        }
    }

    int motherVertex(int V)
    {
        boolean[] visited = new boolean[V];

        int v = -1;

        for(int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                DFSUtil(i, visited);
                v = i;
            }
        }

        // If there exist mother vertex (or vertices)
        // in given graph, then v must be one
        // (or one of them)

        // Now check if v is actually a mother
        // vertex (or graph has a mother vertex).
        // We basically check if every vertex
        // is reachable from v or not.

        // Reset all values in visited[] as false
        // and do DFS beginning from v to check
        // if all vertices are reachable from
        // it or not.
        boolean[] check = new boolean[V];
        DFSUtil(v, check);
        for(boolean val : check)
        {
            if (!val)
            {
                return -1;
            }
        }
        return v;
    }

    // Driver code
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int V = sc.nextInt();
        int E = sc.nextInt();

        Graph_motherVertex g = new Graph_motherVertex(V);

        for(int i=0;i<E;i++){
            int u = sc.nextInt();
            int v = sc.nextInt();

            g.addEdge(u,v);
        }

        System.out.println("The mother vertex is " + g.motherVertex(V));
    }
}

