#include "st.h"
#include <iostream>

int main()
{
    Node *root = getST("1.txt");
    printAST(root);
    return 0;
}
