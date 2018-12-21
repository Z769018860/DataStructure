#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <cstdio>
using namespace std;

typedef struct TreeNode
{
    struct TreeNode* lchild;
    struct TreeNode* rchild;
    char elem;
}TreeNode;

TreeNode *CreateTree()
{
    char c = getchar();
    if(c == '#')
        return NULL;
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->elem = c;
    root->lchild = CreateTree();
    root->rchild = CreateTree();
    return root;
}

void Traversal(TreeNode *root)
{
    if(root == NULL)
        return;
    Traversal(root->lchild);
    cout << root->elem;
    Traversal(root->rchild);
}

int main()
{
    TreeNode *root = CreateTree();
    Traversal(root);
    cout << endl;
}
