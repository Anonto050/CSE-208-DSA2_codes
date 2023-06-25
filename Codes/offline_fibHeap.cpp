#include<bits/stdc++.h>
#include<chrono>

using namespace std;

struct node
{
    double key;
    int id;
    int deg;

    node* parent;
    node* child;
    node* right;
    node* left;

    char mark;
    char c;
};

struct node* Min = NULL;
int path;

class FibonacciHeap
{

public:

    int node_count = 0;


    void fib_connect(struct node* p2, struct node* p1)
    {
        (p2->left)->right = p2->right;
        (p2->right)->left = p2->left;
        if (p1->right == p1)
            Min = p1;
        p2->left = p2;
        p2->right = p2;
        p2->parent = p1;
        if (p1->child == NULL)
            p1->child = p2;
        p2->right = p1->child;
        p2->left = (p1->child)->left;
        ((p1->child)->left)->right = p2;
        (p1->child)->left = p2;
        if (p2->key < (p1->child)->key)
            p1->child = p2;
        p1->deg++;
    }

    void Consolidate()
    {
        int temp1;

        float temp2 = (log(node_count)) / (log(1.6));

        int temp3 = temp2;
        int D = temp3+1;
        struct node* check[D];

        for (int i = 0; i <= temp3; i++)
            check[i] = NULL;
        node* p1 = Min;
        node* p2;
        node* p3;
        node* p4 = p1;
        do
        {
            p4 = p4->right;
            temp1 = p1->deg;
            while (check[temp1] != NULL)
            {
                p2 = check[temp1];
                if (p1->key > p2->key)
                {
                    p3 = p1;
                    p1 = p2;
                    p2 = p3;
                }
                if (p2 == Min)
                    Min = p1;
                fib_connect(p2, p1);
                if (p1->right == p1)
                    Min = p1;
                check[temp1] = NULL;
                temp1++;
            }
            check[temp1] = p1;
            p1 = p1->right;
        } while (p1 != Min);

        Min = NULL;

        for (int j = 0; j <= temp3; j++)
        {
            if (check[j] != NULL)
            {
                check[j]->left = check[j];
                check[j]->right = check[j];
                if (Min != NULL)
                {
                    (Min->left)->right = check[j];
                    check[j]->right = Min;
                    check[j]->left = Min->left;
                    Min->left = check[j];
                    if (check[j]->key < Min->key)
                        Min = check[j];
                }
                else
                {
                    Min = check[j];
                }
                if (Min == NULL)
                    Min = check[j];
                else if (check[j]->key < Min->key)
                    Min = check[j];
            }
        }
    }

    void Insert(double val,int idx)
    {
        struct node* x = new node();

        x->key = val;
        x->id = idx;
        x->deg = 0;
        x->mark = 'W';
        x->c = 'N';
        x->parent = NULL;
        x->child = NULL;
        x->left = x;
        x->right = x;

        if (Min != NULL)
        {
            (Min->left)->right = x;
            x->right = Min;
            x->left = Min->left;
            Min->left = x;
            if (x->key < Min->key)
                Min = x;
        }
        else
        {
            Min = x;
        }
        node_count++;
    }

    node* Extract_min()
    {
        if (Min == NULL)
            cout << "Empty" << endl;
        else
        {
            node* temp = Min;
            node* temp2 = Min;
            node* y;
            y = temp;
            node* x = NULL;

            if (temp->child != NULL)
            {

                x = temp->child;

                //bringing child to root node

                do
                {
                    y = x->right;
                    (Min->left)->right = x;
                    x->right = Min;
                    x->left = Min->left;
                    Min->left = x;

                    if (x->key < Min->key){
                        Min = x;
                    }

                    x->parent = NULL;
                    x = y;
                }
                while (y != temp->child);
            }

            //deleting the node

            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;
            Min = temp->right;


            if (temp->child == NULL && temp == temp->right)
                Min = NULL;
            else
            {
                Min = temp->right;
                Consolidate();
            }
            node_count--;
            return temp2;
        }
    }

    void Cut(struct node* found, struct node* temp)
    {
        if (found == found->right)
            temp->child = NULL;

        (found->left)->right = found->right;
        (found->right)->left = found->left;
        if (found == temp->child)
            temp->child = found->right;

        temp->deg = temp->deg - 1;
        found->right = found;
        found->left = found;
        (Min->left)->right = found;
        found->right = Min;
        found->left = Min->left;
        Min->left = found;

        found->parent = NULL;
        found->mark = 'B';
    }


    void Cascase_cut(struct node* temp)
    {
        node* ptr5 = temp->parent;
        if (ptr5 != NULL)
        {
            if (temp->mark == 'W')
            {
                temp->mark = 'B';
            }
            else
            {
                Cut(temp, ptr5);
                Cascase_cut(ptr5);
            }
        }
    }

    void Decrease_key(struct node* found, double val)
    {
        if (Min == NULL)
            cout << "The Heap is Empty" << endl;

        if (found == NULL)
            cout << "Node not found in the Heap" << endl;

        found->key = val;
        //cout<<found->key<<endl;

        struct node* temp = found->parent;
        if (temp != NULL && found->key < temp->key)
        {
            Cut(found, temp);
            Cascase_cut(temp);
        }
        if (found->key < Min->key)
            Min = found;
    }

    void Find(struct node* Min, int old_val, double val)
    {
        struct node* found = NULL;
        node* temp = Min;
        temp->c = 'Y';
        node* found_ptr = NULL;
        //cout<<endl<<temp->id<<" "<<old_val<<endl;
        int x = temp->id;
        int y = old_val;

        if(y==x)
        {
            found_ptr = temp;
            temp->c = 'N';
            found = found_ptr;
            Decrease_key(found, val);
        }
        if (found_ptr == NULL)
        {
            if (temp->child != NULL)
                Find(temp->child, old_val, val);
            if ((temp->right)->c != 'Y')
                Find(temp->right, old_val, val);
        }
        temp->c = 'N';
        found = found_ptr;
    }
//
//    void Deletion(int val)
//    {
//        if (Min == NULL)
//            cout << "The heap is empty" << endl;
//        else
//        {
//            Find(Min, val, 0);
//
//            Extract_min();
//            cout << "Key Deleted" << endl;
//        }
//    }

};

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
        adj[y].push_back(make_pair(w,x));
    }

    double dijkstra(int s,int d)
    {
        int path_len = 0;

        priority_queue< pair<float,int>,vector<pair<float,int>>,greater<pair<float,int>> > pq;

        vector<float> key(V,INT_MAX);
        vector<int> parent(V,-1);
        vector<bool> visited(V,false);

        int src = s;

        key[src] = 0;
        pq.push(make_pair(0,src));

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

        int i = d;
        while(i!=s)
        {
            path_len++;
            i=parent[i];
        }

        cout<<path_len<<" "<<key[d]<<endl;
        path = path_len;
        return key[d];

    }

    void dijkstra_fib(int s,int d)
    {

        int path_len = 0;

        FibonacciHeap fibH;
        node *p;

        vector<float> key2(V,INT_MAX);
        vector<int> parent2(V,-1);
        vector<bool> visited2(V,false);

        int src = s;

        //key2[src] = 0;
//
        for(int i=0;i<V;i++)
            fibH.Insert(key2[i],i);

         fibH.Find(Min,src,0);
        //fibH.Insert(0,src);

        while(fibH.node_count!=0)
        {
            p = fibH.Extract_min();
            int u = p->id;
            key2[u] = p->key;

            if(visited2[u]==true)
                continue;

            visited2[u] = true;

            list<pair<float,int>> :: iterator i;

            for(i = adj[u].begin(); i != adj[u].end(); i++)
            {
                int v = (*i).second;
                float weight = (*i).first;

                if(visited2[v]==false && key2[v]>weight+key2[u])
                {
                    key2[v] = weight+key2[u];
                    //fibH.Insert(key2[v],v);
                    fibH.Find(Min,v,key2[v]);
                    parent2[v] = u;
                }
            }

        }
        cout<<key2[d]<<endl;
    }

};

int main()
{

    int u,v,E,V,s,d,k;
    double w,res;
    Graph g(1000);

    fstream myfile("in4.txt", ios::in);

    if (myfile.is_open())
    {
        myfile >> V >> E;
        Graph g1(V);
        g = g1;

        for (int i = 0; i < E; i++)
        {
            myfile >> u >> v >> w;
            g.addEdge(u,v,w);
        }
        myfile.close();
    }
    else
        cout << "Unable" << endl;


    fstream myfile2("in2.txt", ios::in);
    fstream myfile3("out.txt", ios::out);

    if (myfile2.is_open() && myfile3.is_open())
    {

        myfile2>>k;

        for(int i=0; i<k; i++)
        {

            myfile2>>s>>d;

            std::chrono::steady_clock::time_point begin1 = std::chrono::steady_clock::now();
            res = g.dijkstra(s,d);
            std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
            double t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin1).count();

            std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
            g.dijkstra_fib(s,d);
            std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
            double t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - begin2).count();

            myfile3<<path<<" "<<res<<" "<<t1<<" "<<t2<<endl;
        }
        myfile2.close();
        myfile3.close();
    }
    else
        cout << "Unable" << endl;
}


