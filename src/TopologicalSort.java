import java.io.*;
import java.util.*;

class Graph_topologicalSort {
    private int V;

    // Adjacency List Representation
    private LinkedList<Integer> adj[];
    // Constructor
    Graph_topologicalSort(int v)
    {
        V = v;
        adj = new LinkedList[v];
        for(int i=0; i<v; ++i)
            adj[i] = new LinkedList();
    }

    // Function to add an edge into the graph

    void addEdge(int v,int w)
    {
        adj[v].add(w);
    }

    // A recursive function used by topologicalSort
    void topologicalSortUtil(int v, boolean visited[], Stack<Integer> stack)
    {
        visited[v] = true;
        Integer i;

        Iterator<Integer> it = adj[v].iterator();

        while (it.hasNext()) {
            i = it.next();
            if (!visited[i])
                topologicalSortUtil(i, visited, stack);
        }

        stack.push(new Integer(v));
    }

    void topologicalSort()
    {
        Stack<Integer> stack = new Stack<Integer>();

        boolean visited[] = new boolean[V];
        for (int i = 0; i < V; i++)
            visited[i] = false;


        for (int i = 0; i < V; i++)
            if (visited[i] == false)
                topologicalSortUtil(i, visited, stack);

        while (stack.empty() == false)
            System.out.print(stack.pop() + " ");
    }

    // Driver code
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        int V = sc.nextInt();
        int E = sc.nextInt();

        Graph_topologicalSort g = new Graph_topologicalSort(V+1);

        for(int i=0;i<E;i++){
            int u = sc.nextInt();
            int v = sc.nextInt();

            g.addEdge(u,v);
        }
        System.out.println("Following is a Topological " + "sort of the given graph");

        g.topologicalSort();
    }
}

