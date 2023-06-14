#include "st.h"

Node *standerdize_let(Node *node)
{
    if (node == nullptr)
        return node;
    if (node->value == "let")
    {
        node->value = "gamma";
        node->left->value = "lambda";
        Node *temp = node->left->left->right;
        node->left->left->right = node->left->right;
        node->left->right = temp;
        standerdize_let(node->left->left->right);
        standerdize_let(node->left->right);
    }
    return node;
}

Node *standerdize(Node *node)
{
    node = standerdize_let(node);
    return node;
}

Node *getST(string filename)
{
    Node *root = getAST(filename);
    root = standerdize(root);
    return root;
}

void printST(Node *node)
{
    printAST(node);
}