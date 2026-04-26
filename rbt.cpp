#include <iostream>
#include <string>
using namespace std;
#define RED 0
#define BLACK 1
struct Node
{
    string dirName;
    int color;
    Node *left;
    Node *right;
    Node *parent;
    Node(string name)
    {
        dirName = name;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};
class RedBlackTree
{
public:
    Node *root;
    Node *NIL;
    RedBlackTree()
    {
        NIL = new Node("");
        NIL->color = BLACK;
        NIL->left = nullptr;
        NIL->right = nullptr;
        root = NIL;
    }
    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }
    void rightRotate(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent =
                y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }
    void insert(string name)
    {
        Node *newNode = new Node(name);
        newNode->left = NIL;
        newNode->right = NIL;
        Node *parent = nullptr;
        Node *current = root;
        while (current != NIL)
        {
            parent = current;
            if (newNode->dirName < current->dirName)
                current = current->left;
            else if (newNode->dirName > current->dirName)
                current = current->right;
            else
            {
                cout << "Directory \"" << name << "\" already exists!\n";
                delete newNode;
                return;
            }
        }
        newNode->parent = parent;
        if (parent == nullptr)
            root = newNode;
        else if (newNode->dirName < parent->dirName)
            parent->left = newNode;
        else
            parent->right = newNode;
        if (newNode->parent == nullptr)
        {
            newNode->color = BLACK;
            return;
        }
        if (newNode->parent->parent == nullptr)
            return;
        insertFix(newNode);
    }
    void insertFix(Node *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *uncle = z->parent->parent->right;
                if (uncle->color == RED)
                {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                Node *uncle = z->parent->parent->left;
                if (uncle->color == RED)
                {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
            if (z == root)
                break;
        }
        root->color = BLACK;
    }
    Node *search(Node *node, string name)
    {
        if (node == NIL || node->dirName == name)
            return node;
        if (name < node->dirName)
            return search(node->left,
                          name);
        return search(node->right, name);
    }
    Node *minimum(Node *node)
    {
        while (node->left != NIL)
            node = node->left;
        return node;
    }
    void transplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    void deleteDir(string name)
    {
        Node *z = search(root, name);
        if (z == NIL)
        {
            cout << "Directory \"" << name << "\" not found!\n";
            return;
        }
        Node *y = z;
        Node *x;
        int originalColor = y->color;
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            originalColor = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (originalColor == BLACK)
            deleteFix(x);
        cout << "Directory \"" << name << "\" deleted successfully!\n";
    }
    void deleteFix(Node *x)
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                Node *w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node *w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    void inOrder(Node *node)
    {
        if (node != NIL)
        {
            inOrder(node->left);
            cout << node->dirName << " [" << (node->color == RED ? "RED" : "BLACK") << "]\n";
        }
    }
    
    void searchDir(string name)
    {
        Node *result = search(root, name);
        if (result == NIL)
            cout << "Directory \"" << name << "\" not found!\n";
        else
            cout << "Directory \"" << result->dirName << "\" found! Color: "
                 << (result->color == RED ? "RED" : "BLACK") << "\n";
    }
};
int main()
{
    RedBlackTree fs;
    while (true)
    {
        cout << "\n====== File System Directory Manager ======\n";
        cout << "1. Create Directory (Insert)\n";
        cout << "2. Delete Directory\n";
        cout << "3. Search Directory\n";
        cout << "4. Display All Directories (In-Order)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        string name;
        switch (choice)
        {
        case 1:
            cout << "Enter directory name: ";
            cin >> name;
            fs.insert(name);
            cout << "Directory \"" << name << "\" created successfully!\n";
            break;
        case 2:
            cout << "Enter directory name to delete: ";
            cin >> name;
            fs.deleteDir(name);
            break;
        case 3:
            cout << "Enter directory name to search: ";
            cin >> name;
            fs.searchDir(name);
            break;
        case 4:
            cout << "\n--- All Directories (Sorted In-Order) ---\n";
            fs.inOrder(fs.root);
            break;
        case 5:
            cout << "Exiting File System. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}