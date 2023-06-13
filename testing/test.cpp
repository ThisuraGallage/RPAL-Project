#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

enum Token
{
    T_begin,
    T_end,
    T_id,
    T_assign,
    T_semicolon,
    T_plus,
    T_star,
    T_lparen,
    T_rparen
};

struct Node
{
    string value;
    Node *left;
    Node *right;
    Node(string v, Node *l = nullptr, Node *r = nullptr) : value(v), left(l), right(r) {}
};

Token next_token;
string token_value;
stack<Node *> nodeStack;
vector<string> tokens;
int token_index = 0;

void Read(Token expected)
{
    if (next_token != expected)
    {
        cout << "Error: unexpected token" << endl;
        exit(1);
    }
    if (token_index >= tokens.size())
    {
        return;
    }
    string input = tokens[token_index++];
    if (input == "begin")
        next_token = T_begin;
    else if (input == "end")
        next_token = T_end;
    else if (input == ":=")
        next_token = T_assign;
    else if (input == ";")
        next_token = T_semicolon;
    else if (input == "+")
        next_token = T_plus;
    else if (input == "*")
        next_token = T_star;
    else if (input == "(")
        next_token = T_lparen;
    else if (input == ")")
        next_token = T_rparen;
    else
    {
        next_token = T_id;
        token_value = input;
    }
}

void Build_tree(string x, int n)
{
    Node *p = nullptr;
    for (int i = 1; i <= n; i++)
    {
        Node *c = nodeStack.top();
        nodeStack.pop();
        c->right = p;
        p = c;
    }
    nodeStack.push(new Node(x, p, nullptr));
}

void P();
void T();
void E();

void S()
{
    int N = 1;
    switch (next_token)
    {
    case T_begin:
        Read(T_begin);
        S();
        while (next_token == T_begin || next_token == T_id)
        {
            S();
            N++;
        }
        Read(T_end);
        Build_tree("block", N);
        break;
    case T_id:
        nodeStack.push(new Node(token_value));
        Read(T_id);
        Read(T_assign);
        E();
        Read(T_semicolon);
        Build_tree("assign", 2);
        break;
    default:
        cout << "Error: unexpected token" << endl;
        exit(1);
    }
}

void E()
{
    T();
    while (next_token == T_plus)
    {
        Read(T_plus);
        T();
        Build_tree("+", 2);
    }
}

void T()
{
    P();
    if (next_token == T_star)
    {
        Read(T_star);
        P();
        Build_tree("*", 2);
    }
}

void P()
{
    switch (next_token)
    {
    case T_lparen:
        Read(T_lparen);
        E();
        Read(T_rparen);
        break;
    case T_id:
        nodeStack.push(new Node(token_value));
        Read(T_id);
        break;
    default:
        cout << "Error: unexpected token" << endl;
        exit(1);
    }
}

void print_tree(Node *node, int indent = 0)
{
    if (!node)
        return;
    for (int i = 0; i < indent; i++)
        cout << ".";
    cout << node->value << endl;
    print_tree(node->left, indent + 1);
    print_tree(node->right, indent);
}

int main()
{

    // Test case
    string test_input = "begin id1 := ( id2 + id3 ) * ( id4 + id5 ) ; end";

    // Tokenize the test input
    size_t start = 0, end = 0;
    while ((end = test_input.find(' ', start)) != string::npos)
    {
        tokens.push_back(test_input.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(test_input.substr(start));

    // Initialize the first token
    string input = tokens[token_index++];
    if (input == "begin")
        next_token = T_begin;
    else if (input == "end")
        next_token = T_end;
    else if (input == ":=")
        next_token = T_assign;
    else if (input == ";")
        next_token = T_semicolon;
    else if (input == "+")
        next_token = T_plus;
    else if (input == "*")
        next_token = T_star;
    else if (input == "(")
        next_token = T_lparen;
    else if (input == ")")
        next_token = T_rparen;
    else
    {
        next_token = T_id;
        token_value = input;
    }

    S();

    Node *root = nodeStack.top();

    cout << "AST:" << endl;

    print_tree(root);

    return 0;
}
