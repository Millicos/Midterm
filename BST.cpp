#include <iostream>
#include <string>
using namespace std;
typedef int Key; // non-negative number
const Key nullKey = -1;
class BSTree
{
private:
    struct Node
    {
        Key key;
        Node *left, *right;
        Node(Key key)
        {
            this->key = key;
            left = nullptr;
            right = nullptr;
        }
    };
    typedef Node *link;

private:
    link root;

public:
    BSTree()
    {
        root = nullptr;
    }
    void printTree(link t, int h)
    {
        if (t == nullptr)
        {
            for (int i = 0; i < h; i++)
                cout << "   ";
            cout << "*  " << endl;
            return;
        }
        printTree(t->right, h + 1);
        for (int i = 0; i < h; i++)
            cout << "   ";
        cout << t->key << endl;
        printTree(t->left, h + 1);
    }
    void printTree()
    {
        printTree(root, 0);
    }
    void insertKey(Key key, link &root)
    {
        if(root == nullptr) {
            root = new Node(key);
        }
        if(key == root->key) return;
        if(key < root->key) {
            insertKey(key, root->left);
        }
        else if(key > root->key) {
            insertKey(key, root->right);
        }
    }
    void insert(Key key)
    {
        insertKey(key, root);
    }
};
int main()
{
    BSTree tree;
    tree.insert(53);
    tree.insert(41);
    tree.insert(71);
    tree.insert(21);
    tree.insert(15);
    tree.insert(52);
    tree.insert(65);
    tree.insert(69);
    tree.insert(79);
    tree.insert(91);
    tree.printTree();
    return 0;
}
