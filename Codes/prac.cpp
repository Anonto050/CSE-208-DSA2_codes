#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *parent;
    Node *left;
    Node *right;
    string color;
    int value;
    int node_count;
};

typedef Node *NodePtr;

class RedBlackTree
{
private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent)
    {
        node->value = 0;
        node->node_count = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = "black";
    }

    NodePtr searchTreeHelper(NodePtr node, int key)
    {
        if (node == TNULL || key == node->value)
        {
            return node;
        }

        if (key < node->value)
        {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == "black")
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == "red")
                {
                    s->color = "black";
                    x->parent->color = "red";
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == "black" && s->right->color == "black")
                {
                    s->color = "red";
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == "black")
                    {
                        s->left->color = "black";
                        s->color = "red";
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "black";
                    s->right->color = "black";
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == "red")
                {
                    s->color = "black";
                    x->parent->color = "red";
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == "black" && s->right->color == "black")
                {
                    s->color = "red";
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == "black")
                    {
                        s->right->color = "black";
                        s->color = "red";
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "black";
                    s->left->color = "black";
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "black";
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key)
    {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL)
        {
            if (node->value == key)
            {
                z = node;
            }

            if (node->value <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == TNULL)
        {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        string y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        countDecUp(z->parent);
        delete z;


        if (y_original_color == "black")
        {
            deleteFix(x);
        }
    }

    // For balancing the tree after Insertion
    void fix_Insert(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == "red")
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == "red")
                {
                    u->color = "black";
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == "red")
                {
                    u->color = "black";
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "black";
                    k->parent->parent->color = "red";
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = "black";
    }


public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->node_count = 0;
        TNULL->color = "black";
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != TNULL)
        {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x)
    {
        if (x->right != TNULL)
        {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        if (x->left != TNULL)
        {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;

         x->node_count = x->left->node_count + x->right->node_count + 1;
        y->node_count = y->left->node_count + y->right->node_count + 1;
    }

    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;

        x->node_count = x->left->node_count + x->right->node_count + 1;
        y->node_count = y->right->node_count + y->left->node_count + 1;
    }

    void countIncUp (NodePtr z)
    {
        if(z == NULL)
            return;
        NodePtr temp = z;
        while(temp != NULL)
        {
            temp->node_count++;
            temp = temp->parent;
        }
    }
    void countDecUp (NodePtr z)
    {
        if(z == NULL)
            return;
        NodePtr temp = z;
        while(temp != NULL)
        {
            temp->node_count--;
            temp = temp->parent;
        }
    }



    bool searchTree(int k)
    {
        NodePtr y = searchTreeHelper(this->root, k);
        if(y == TNULL)
            return false;
        return true;
    }

    // Inserting a node
    void Insert(int key)
    {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->value = key;
        node->node_count = 1;

        node->left = TNULL;
        node->right = TNULL;
        node->color = "red";

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->value < x->value)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->value < y->value)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = "black";
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        countIncUp(node->parent);

        fix_Insert(node);
    }

    NodePtr getRoot()
    {
        return this->root;
    }

    void deleteNode(int value)
    {
        deleteNodeHelper(this->root, value);
    }

    int lowerPriority(int n, NodePtr v)
    {
        if(v == TNULL)
            return 0;
        if(v->value >= n)
            return lowerPriority(n, v->left);
        else
            return (v->left->node_count + 1 + lowerPriority(n, v->right));
    }

};

int main()
{
    RedBlackTree RBT;
    int N,e,x;

    fstream myfile("in.txt", ios::in);
    fstream myfile2("out.txt", ios::out);

    if (myfile.is_open() && myfile2.is_open())
    {
        myfile>>N;
        myfile2<<N<<endl;
        cout<<N<<endl;

        int ans;

        for(int i=0; i<N; i++)
        {
            myfile>>e>>x;

            if(e==0)
            {
                if(RBT.searchTree(x))
                {
                    RBT.deleteNode(x);
                    ans = 1 ;
                }
                else
                {
                    ans = 0 ;
                }

            }
            else if(e==1)
            {
                if(RBT.searchTree(x))
                {
                    ans = 0 ;
                }
                else
                {
                    RBT.Insert(x);
                    ans = 1;
                }
            }
            else if(e==2)
            {
                if(RBT.searchTree(x))
                    ans = 1;
                else
                    ans = 0;
            }
            else
            {
                ans = RBT.lowerPriority(x,RBT.getRoot());
            }
            myfile2<<e<<" "<<x<<" "<<ans<<endl;
            cout<<e<<" "<<x<<" "<<ans<<endl;
        }
           myfile.close();
           myfile2.close();
    }

    else
        cout<<"Unable"<<endl;

}
