#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;
    int lth, rth;

    Node(int data)
    {
        this->data = data;
        lth = rth = 1;
        left = right = NULL;
    }
};

class TBT
{
public:
    Node *insert(Node *root, int key)
    {
        Node *temp = new Node(key);
        Node *parent = NULL;

        if (root == NULL)
        {
            root = temp;
        }
        else
        {
            Node *curr = root;

            while (curr != NULL)
            {
                if (key == curr->data)
                {
                    cout << "Duplicate key not allowed\n";
                    return root;
                }

                parent = curr;

                if (key < curr->data)
                {
                    if (curr->lth == 0)
                        curr = curr->left;
                    else
                        break;
                }
                else
                {
                    if (curr->rth == 0)
                        curr = curr->right;
                    else
                        break;
                }
            }

            if (key < parent->data)
            {
                temp->left = parent->left;
                temp->right = parent;
                parent->lth = 0;
                parent->left = temp;
            }
            else
            {
                temp->left = parent;
                temp->right = parent->right;
                parent->rth = 0;
                parent->right = temp;
            }
        }
        return root;
    }

    Node *leftMost(Node *root)
    {
        while (root->lth == 0)
            root = root->left;
        return root;
    }

    void inorder(Node *root)
    {
        if (root == NULL)
        {
            cout << "Tree is empty\n";
            return;
        }

        Node *curr = leftMost(root);

        while (curr != NULL)
        {
            cout << curr->data << " ";

            if (curr->rth == 1)
                curr = curr->right;
            else
                curr = leftMost(curr->right);
        }
        cout << endl;
    }
};

int main()
{
    TBT tbt;
    Node *root = NULL;
    int choice, value;

    do
    {
        cout << "\n1. Insert\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            root = tbt.insert(root, value);
            break;

        case 2:
            cout << "Inorder: ";
            tbt.inorder(root);
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (choice != 3);

    return 0;
}