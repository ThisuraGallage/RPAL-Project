#ifndef AST_H
#define AST_H

#include "lexical_scanner.h"

struct Node
{
    string value;
    TokenType type;
    Node *left;
    Node *right;
    Node(string v, TokenType t, Node *l = nullptr, Node *r = nullptr) : value(v), type(t), left(l), right(r) {}
};

Node *getAST(string filename);
void printAST(Node *node);

#endif