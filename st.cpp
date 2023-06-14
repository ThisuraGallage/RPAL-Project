#include "st.h"

Node *standerdize_let(Node *node)
{
    if (node == nullptr)
        return node;
    node->value = "gamma";
    node->left->value = "lambda";
    Node *temp = node->left->left->right;
    node->left->left->right = node->left->right;
    node->left->right = temp;
    return node;
}

// Function to perform post-order traversal
void postOrderTraversal(Node *node)
{
    if (node == nullptr)
        return;

    // Traverse left subtree
    postOrderTraversal(node->left);

    // Traverse right subtree
    postOrderTraversal(node->right);

    // Process current node
    if (node->value == "let")
    {
        node = standerdize_let(node);
    }

    // You can perform additional operations on the current node if needed
    // based on its TokenType or other properties.
}

Node *standerdize(Node *node)
{
    postOrderTraversal(node);
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