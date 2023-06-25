import java.util.*;

class Graph_cyclicDirected {

    private int V;

    // Adjacency List Representation
    private LinkedList<Integer> adj[];

    // Constructor
    Graph_cyclicDirected(int v)
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

    private boolean isCyclicUtil(int i, boolean[] visited, boolean[] recStack)
    {
        if (recStack[i])
            return true;

        if (visited[i])
            return false;

        visited[i] = true;
        recStack[i] = true;

        Integer x;

        Iterator<Integer> it = adj[i].iterator();
        while (it.hasNext()) {
            x = it.next();
            if (isCyclicUtil(x, visited, recStack))
                return true;
        }

        recStack[i] = false;

        return false;
    }

    private boolean isCyclic()
    {
        boolean[] visited = new boolean[V];
        boolean[] recStack = new boolean[V];

        for (int i = 0; i < V; i++)
            if (isCyclicUtil(i, visited, recStack))
                return true;

        return false;
    }

    // Driver code
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int V = sc.nextInt();
        int E = sc.nextInt();

        Graph_cyclicDirected g = new Graph_cyclicDirected(V);

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

