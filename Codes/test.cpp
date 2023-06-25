#include<bits/stdc++.h>
using namespace std;

enum Color {
    red,
    black
};

class node {
public:
    int nCount;
    Color color;
    int key;
    node* left;
    node* right;
    node* parent;

    node(int val = 0)
    {
        nCount = 1;
        key = val;
        left = right = parent = NULL;
        color = red;
    }

    // check if node is left child of parent
    bool isALeftChild()
    {
        if (parent != NULL && this == parent->left)
            return true;
        else
            return false;
    }

    //return a pointer to the Uncle
    node* uncle()
    {
        // If no parent or grandparent, then no uncle
        if (parent == NULL || parent->parent == NULL)
            return NULL;
        // uncle on right
        else if (parent->isALeftChild())
            return parent->parent->right;
        // uncle on left
        else
            return parent->parent->left;
    }

    //return a pointer to the sibling
    node *sibling() {
        // sibling null if no parent
        if (parent == NULL)
            return NULL;
        else if (this->isALeftChild())
            return parent->right;
        else
            return parent->left;
    }

    // check if node has a red colored child node
    bool hasRedChild()
    {
        if((left != NULL && left->color == red) || (right != NULL && right->color == red))
            return true;
        else
            return false;
    }

    // move down the node and bring a new node in it's place, making it the former one's parent
    void moveDown(node* newParent)
    {
        if(this->parent != NULL)
        {
            if(this->isALeftChild())
                parent->left = newParent;
            else
                parent->right = newParent;
        }
        newParent->parent = this->parent;
        this->parent = newParent;
    }

};


class RBtree{

public:
    node* nil;
    node* root;
    RBtree()
    {
        nil = new node();
        nil->color = black;
        nil->nCount = 0;
        root = nil;
    }

    void leftRotate(node* x)
    {
        node* y = x->right;
        x->right = y->left;

        if(y->left != nil)
            y->left->parent = x;
        y->parent = x->parent;
        if(x->parent == nil)
            root = y;
        else if(x->isALeftChild())
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;

        x->nCount = x->left->nCount + x->right->nCount + 1;
        y->nCount = y->left->nCount + y->right->nCount + 1;
    }

    void rightRotate(node* x)
    {
        node* y = x->left;
        x->left = y->right;



        if(y->right != nil)
            y->right->parent = x;
        y->parent = x->parent;
        if(x->parent == nil)
            root = y;
        else if(x->isALeftChild())
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;

        x->nCount = x->left->nCount + x->right->nCount + 1;
        y->nCount = y->right->nCount + y->left->nCount + 1;
    }

    void countIncUp (node* z)
    {
        if(z == nil)
            return;
        node* temp = z;
        while(temp != nil)
        {
            temp->nCount++;
            temp = temp->parent;
        }
    }
    void countDecUp (node* z)
    {
        if(z == nil)
            return;
        node* temp = z;
        while(temp != nil)
        {
            temp->nCount--;
            temp = temp->parent;
        }
    }

    node *successor(node *x)
    {
        if(x->right == nil)
            return nil;
        node *temp = x->right;
        while (temp->left != nil)
            temp = temp->left;
        return temp;
    }
    void swapColors(node *x1, node *x2)
    {
        Color temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }
    void swapKeys(node *u, node *v)
    {
        int temp;
        temp = u->key;
        u->key = v->key;
        v->key = temp;
    }

    void RB_insert(int z1)
    {
        node* z = new node(z1);
        node* y = nil;
        node* x = root;

        while(x != nil)
        {
            y = x;
            if(z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;

        if(y == nil)
            root = z;
        else if(z->key < y->key)
            y->left = z;
        else
            y->right = z;

        z->left = z->right = nil;
        z->color = red;

        countIncUp(z->parent);
        RB_insertFixup(z);
    }

    void RB_insertFixup(node* z)
    {
        node* y = nil;
        while(z->parent != nil && z->parent->color == red)
        {
            if(z->parent->isALeftChild())
            {
                y = z->parent->parent->right;
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    rightRotate(z->parent->parent);
                }
            }
            else if(z->parent->parent != nil)
            {
                y = z->parent->parent->left;
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = black;
    }

    node* RB_delete(node* z)
    {
        node* y = nil;
        if(z->left == nil || z->right == nil)
            y = z;
        else
            y = successor(z);

        node* x = nil;
        if(y->left != nil)
            x = y->left;
        else
            x = y->right;

        x->parent = y->parent;

        if(y->parent == nil)
            root = x;
        else if(y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;

        if(y != z)
            swapKeys(z, y);

        countDecUp(y->parent);
        if(y->color == black)
            RB_deleteFixup(x);
        return y;
    }

    void RB_deleteFixup(node* x)
    {
        node* w = nil;
        while (x->color == black && x != root)
        {
            if(x == x->parent->left)
            {
                w = x->parent->right;
                if(w->color == red)
                {
                    w->color = black;
                    x->parent->color = red;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == black && w->right->color == black)
                {
                    w->color = red;
                    x = x->parent;
                }
                else
                {
                    if(w->right->color == black)
                    {
                        w->left->color = black;
                        w->color = red;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    leftRotate(x->parent);
                    x = root;
                }
            }

            else
            {
                w = x->parent->left;
                if(w->color == red)
                {
                    w->color = black;
                    x->parent->color = red;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == black && w->left->color == black)
                {
                    w->color = red;
                    x = x->parent;
                }
                else
                {
                    if(w->left->color == black)
                    {
                        w->right->color = black;
                        w->color = red;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = black;
    }

    node *search(int n)
    {
        bool found = false;
        node *temp = root;
        while (temp != nil) {
            if (n < temp->key) {
                if (temp->left == nil)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->key) {
                found = true;
                break;
            }
            else {
                if (temp->right == nil)
                    break;
                else
                    temp = temp->right;
            }
        }

        if(found) return temp;
        else return nil;
    }

    void deleteByVal(int n)
    {
        if (root == nil)
      // Tree is empty
            return;
        node *v = search(n);
        if (v->key != n) {
            cout << "No node found to delete with value: " << n << endl;
            return;
        }
        RB_delete(v);
    }

    // prints level order for given node
    void levelOrder(node *x)
    {
        if (x == nil)
        // return if node is null
            return;

        // queue for level order
        queue<node *> q;
        node *curr;
        q.push(x);

        while (!q.empty())
        {
            // while q is not empty
            // dequeue
            curr = q.front();
            q.pop();

            // print node value
            cout << curr->key << " ";

            // push children to queue
            if (curr->left != nil)
                q.push(curr->left);
            if (curr->right != nil)
                q.push(curr->right);
        }
    }
    // prints level order of the tree
    void printLevelOrder()
    {
        cout << "Level order: " << endl;
        if (root == nil)
            cout << "Tree is empty" << endl;
        else
            levelOrder(root);
        cout << endl;
    }
    // prints inorder recursively
    void inorder(node *x)
    {
        if (x == nil)
            return;
        inorder(x->left);
        cout << x->key << "(" << x->nCount << ") ";
        inorder(x->right);
  }
    // prints inorder of the tree
    void printInOrder()
    {
        cout << "Inorder: " << endl;
        if (root == nil)
            cout << "Tree is empty" << endl;
        else
            inorder(root);
        cout << endl;
    }

    int lowerPriority(int n, node* v)
    {
        if(v == nil)
            return 0;
        if(v->key >= n)
            return lowerPriority(n, v->left);
        else
            return (v->left->nCount + 1 + lowerPriority(n, v->right));
    }

};


int main()
{
    RBtree tree;
    int nLines, cmd, pr;

    fstream myfile("in.txt", ios::in);
    if (myfile.is_open())
    {
        myfile >> nLines;
        for (int i = 0; i < nLines; i++)
        {
            myfile >> cmd >> pr;
            if(cmd == 0)
            {
                node* p = tree.search(pr);
                if(p == tree.nil)
                    cout << 0 << endl;
                else
                {
                    tree.deleteByVal(pr);
                    cout << 1 << endl;
                }
            }
            else if (cmd == 1)
            {
                node* p = tree.search(pr);
                if(p != tree.nil)
                    cout << 0 << endl;
                else
                {
                    tree.RB_insert(pr);
                    cout << 1 << endl;
                }
            }
            else if (cmd == 2)
            {
                node* p = tree.search(pr);
                if(p == tree.nil)
                    cout << 0 << endl;
                else
                    cout << 1 << endl;
            }
            else if (cmd == 3)
            {
                cout << tree.lowerPriority(pr, tree.root) << endl;
            }
            else
            {
                cout << "Invalid input\n";
            }
        }
        myfile.close();
    }
    else
        cout << "Unable to open file" << endl;


/*
    tree.RB_insert(7);
    tree.RB_insert(3);
    tree.RB_insert(18);
    tree.RB_insert(22);
    tree.RB_insert(10);
    tree.RB_insert(11);
    tree.RB_insert(8);
    tree.RB_insert(26);
    tree.RB_insert(2);
    tree.RB_insert(6);
    tree.RB_insert(13);

    tree.printInOrder();
    tree.printLevelOrder();

    cout<<endl<<"Deleting 18, 11, 3, 10, 22"<<endl;

    tree.deleteByVal(18);
    tree.deleteByVal(11);
    tree.deleteByVal(3);
    tree.deleteByVal(10);
    tree.deleteByVal(22);

    tree.printInOrder();
    tree.printLevelOrder();

    cout << tree.lowerPriority(0, tree.root);
*/

    return 0;
}

