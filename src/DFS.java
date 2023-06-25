import java.io.*;
import java.util.*;

class Graph_dfs {
    private int V;


    private LinkedList<Integer> adj[];

    // Constructor
    @SuppressWarnings("unchecked")
    Graph_dfs(int v) {
        V = v;
        adj = new LinkedList[v];
        for (int i = 0; i < v; ++i)
            adj[i] = new LinkedList();
    }

    // Function to add an edge into the graph
    void addEdge(int v, int w) {
        adj[v].add(w); // Add w to v's list.
        //adj[w].add(v); //Undirected
    }

    // A function used by DFS
    void DFSUtil(int v, boolean visited[]) {

        visited[v] = true;
        System.out.print(v + " ");

        Iterator<Integer> i = adj[v].listIterator();
        while (i.hasNext()) {
            int n = i.next();
            if (!visited[n])
                DFSUtil(n, visited);
        }
    }

    void DFS(int v) {

        boolean visited[] = new boolean[V];

        DFSUtil(v, visited);
    }

    // Driver Code
        public static void main(String args[]) {

            Scanner sc = new Scanner(System.in);
            int V = sc.nextInt();
            int E = sc.nextInt();

            Graph_dfs g = new Graph_dfs(V);

            for(int i=0;i<E;i++){
                int u = sc.nextInt();
                int v = sc.nextInt();

                g.addEdge(u,v);
            }

            System.out.println(
                    "Following is Depth First Traversal "
                            + "(starting from vertex 2)");

            g.DFS(2);
        }

}



