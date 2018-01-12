#include <iostream>
#include <vector>
using namespace std;

struct Node 
{
    int val = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int v) : val(v)
    {}
};

const Node* LCA(const Node* root, int a, int b, bool& aFound, bool& bFound)
{
    if (!root)
    {
        return root;
    }
    else if (root->val == a)
    {
        aFound = true;
        return root;
    }
    else if (root->val == b)
    {
        bFound = true;
        return root;
    }

    const Node* left = LCA(root->left, a, b, aFound, bFound);
    const Node* right = LCA(root->right, a, b, aFound, bFound);
    if (left && right)
    {
        return root;
    }
    return (left != nullptr) ? left : right;
}

bool find(const Node* root, int val)
{
    if (!root)
    {
        return false;
    }
    else if (root->val == val)
    {
        return true;
    }
    return find(root->left, val) || find(root->right, val);
}

const Node* findLCA(const Node* root, int a, int b)
{
    if (!root)
    {
        return root;
    }

    bool aFound = false, bFound = false;
    const Node* lca = LCA(root, a, b, aFound, bFound);
    if ((aFound && bFound) || (aFound && find(lca, b)) || (bFound && find(lca, a)))
    {
        return lca;
    }
    return nullptr;
}

int main()
{
    /*          
                1
              /   \
            2       3
          /   \   /   \
         4     5 6     7
    */
    Node* root = new(std::nothrow) Node(1);
    root->left = new(std::nothrow) Node(2);
    root->right = new(std::nothrow) Node(3);
    root->left->left = new(std::nothrow) Node(4);
    root->left->right = new(std::nothrow) Node(5);
    root->right->left = new(std::nothrow) Node(6);
    root->right->right = new(std::nothrow) Node(7);

    cout << "LCA(4, 5) = " << findLCA(root, 4, 5)->val << endl;
    cout << "LCA(4, 6) = " << findLCA(root, 4, 6)->val << endl;
    cout << "LCA(3, 4) = " << findLCA(root, 3, 4)->val << endl;
    cout << "LCA(2, 4) = " << findLCA(root, 2, 4)->val << endl;

    return 0;
}