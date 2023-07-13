#include "ast.h"
#include <iostream>

int main()
{
    Node *root = getAST("1.txt");
    printAST(root);
    return 0;
}
