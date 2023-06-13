// #include <iostream>
// #include <string>
// #include <stack>
// #include <vector>
// #include "lexical_scanner.h"
// using namespace std;

// enum Token
// {
//     T_let,
//     T_fn,
//     T_identifier,
//     T_dot,
//     T_where,
//     T_semicolon
// };

// struct Node
// {
//     string value;
//     Node *left;
//     Node *right;
//     Node(string v, Node *l = nullptr, Node *r = nullptr) : value(v), left(l), right(r) {}
// };

// Token next_token;
// string token_value;
// stack<Node *> nodeStack;
// vector<Token> tokens;
// int token_index = 0;

// void Read(Token expected)
// {
//     if (next_token != expected)
//     {
//         cout << "Error: unexpected token" << endl;
//         exit(1);
//     }
//     if (token_index >= tokens.size())
//     {
//         return;
//     }
//     Token token = tokens[token_index++];
//     switch (token)
//     {
//         case T_let:
//             next_token = T_let;
//             break;
//         case T_fn:
//             next_token = T_fn;
//             break;
//         case T_identifier:
//             next_token = T_identifier;
//             token_value = token_value; // Update token_value accordingly
//             break;
//         case T_dot:
//             next_token = T_dot;
//             break;
//         case T_where:
//             next_token = T_where;
//             break;
//         case T_semicolon:
//             next_token = T_semicolon;
//             break;
//         default:
//             cout << "Error: unexpected token" << endl;
//             exit(1);
//     }
// }

// void Build_tree(string x, int n)
// {
//     Node *p = nullptr;
//     for (int i = 1; i <= n; i++)
//     {
//         Node *c = nodeStack.top();
//         nodeStack.pop();
//         c->right = p;
//         p = c;
//     }
//     nodeStack.push(new Node(x, p, nullptr));
// }

// void E();
// void Ew();
// void T();
// void D();
// void Dr();
// void Vb();

// void S()
// {
//     switch (next_token)
//     {
//         case T_let:
//             Read(T_let);
//             D();
//             Read(T_in);
//             E();
//             Build_tree("let", 2);
//             break;
//         case T_fn:
//             Read(T_fn);
//             Vb();
//             while (next_token == T_identifier)
//             {
//                 Vb();
//             }
//             Read(T_dot);
//             E();
//             Build_tree("lambda", 2);
//             break;
//         default:
//             Ew();
//     }
//     if (next_token == T_semicolon)
//     {
//         Read(T_semicolon);
//     }
// }

// void E()
// {
//     T();
//     while (next_token == T_semicolon)
//     {
//         Read(T_semicolon);
//         T();
//         Build_tree(";", 2);
//     }
// }

// void Ew()
// {
//     T();
//     if (next_token == T_where)
//     {
//         Read(T_where);
//         Dr();
//         Build_tree("where", 2);
//     }
// }

// void T()
// {
//     switch (next_token)
//     {
//         case T_let:
//             Read(T_let);
//             D();
//             Read(T_in);
//             E();
//             Build_tree("let", 2);
//             break;
//         case T_fn:
//             Read(T_fn);
//             Vb();
//             while (next_token == T_identifier)
//             {
//                 Vb();
//             }
//             Read(T_dot);
//             E();
//             Build_tree("lambda", 2);
//             break;
//         default:
//             if (next_token == T_identifier)
//             {
//                 Read(T_identifier);
//                 Build_tree(token_value, 0);
//             }
//             else
//             {
//                 cout << "Error: unexpected token" << endl;
//                 exit(1);
//             }
//     }
// }

// void D()
// {
//     switch (next_token)
//     {
//         case T_identifier:
//             Read(T_identifier);
//             if (next_token == T_semicolon)
//             {
//                 Build_tree(";", 1);
//                 return;
//             }
//             Read(T_identifier);
//             Read(T_semicolon);
//             Build_tree(";", 2);
//             D();
//             break;
//         default:
//             cout << "Error: unexpected token" << endl;
//             exit(1);
//     }
// }

// void Dr()
// {
//     switch (next_token)
//     {
//         case T_semicolon:
//             Read(T_semicolon);
//             D();
//             break;
//         default:
//             // Do nothing for epsilon production
//             break;
//     }
// }

// void Vb()
// {
//     switch (next_token)
//     {
//         case T_identifier:
//             Read(T_identifier);
//             break;
//         default:
//             cout << "Error: unexpected token" << endl;
//             exit(1);
//     }
// }

// void print_tree(Node *node, int indent = 0)
// {
//     if (!node)
//         return;
//     for (int i = 0; i < indent; i++)
//         cout << ".";
//     cout << node->value << endl;
//     print_tree(node->left, indent + 1);
//     print_tree(node->right, indent);
// }

// int main()
// {
//     // Test case
//     string test_input = "let x = 1 in Print x";

//     // Tokenize the test input using the lexical scanner
//     tokens = tokenizeFile(test_input);

//     // Initialize the first token
//     Token token = tokens[token_index++];
//     switch (token)
//     {
//         case T_let:
//             next_token = T_let;
//             break;
//         default:
//             cout << "Error: unexpected token" << endl;
//             exit(1);
//     }

//     S();

//     Node *root = nodeStack.top();

//     cout << "AST:" << endl;

//     print_tree(root);

//     return 0;
// }
