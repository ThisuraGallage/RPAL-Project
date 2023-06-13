#include "lexical_scanner.h"
#include "ast.h"
#include <iostream>
#include <unordered_set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

Token next_token;
vector<Token> tokens;
stack<Node *> nodeStack;
int token_index = 0;

bool isStringInList(const vector<string> &stringList, const string &searchString)
{
    unordered_set<string> stringSet(stringList.begin(), stringList.end());
    return stringSet.find(searchString) != stringSet.end();
}
bool isKeyWord(const string &s)
{
    vector<string> keyWords = {"let", "where", "in", "fn", "and", "rec", "within", "aug", "not", "or", "gr", "ge", "ls", "le", "eq", "ne", "true", "false", "nil", "dummy"};
    return isStringInList(keyWords, s);
}

void Read(string expected)
{
    if (next_token.value != expected)
    {
        cout << "Error: unexpected token" << endl;
        exit(1);
    }
    if (token_index >= (int)tokens.size())
    {
        next_token.value = "";
        next_token.type = NAN;
        return;
    }
    next_token = tokens[token_index++];
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
    nodeStack.push(new Node(x, NAN, p, nullptr));
}

void D();
void Da();
void Db();
void Dr();
void Vb();
void Vl();
void E();
void Ew();
void T();
void Ta();
void Tc();
void B();
void Bt();
void Bs();
void Bp();
void A();
void At();
void Af();
void Ap();
void R();
void Rn();

void E()
{

    if (next_token.value == "let")
    {
        Read("let");
        D();
        Read("in");
        E();
        Build_tree("let", 2);
    }
    else if (next_token.value == "fn")
    {
        Read("fn");
        int n = 0;
        while ((next_token.value == "(") or (next_token.type == IDENTIFIER))
        {
            Vb();
            n++;
        }
        Read(".");
        E();
        Build_tree("lambda", n + 1);
    }
    else
    {
        Ew();
    }
}

void Ew()
{
    T();
    if (next_token.value == "where")
    {
        Read("where");
        Dr();
        Build_tree("where", 2);
    }
}

void T()
{
    Ta();
    int n = 0;
    while (next_token.value == ",")
    {
        n++;
        Read(",");
        Ta();
    }
    if (n > 0)
    {
        Build_tree("tau", n + 1);
    }
}

void Ta()
{
    Tc();
    while (next_token.value == "aug")
    {
        Read("aug");
        Tc();
        Build_tree("aug", 2);
    }
}

void Tc()
{
    B();
    if (next_token.value == "->")
    {
        Read("->");
        Tc();
        Read("|");
        Tc();
        Build_tree("->", 3);
    }
}

// B -> B ’or’ Bt => ’or’
// -> Bt ;
void B()
{
    Bt();
    while (next_token.value == "or")
    {
        Read("or");
        Bt();
        Build_tree("or", 2);
    }
}

// Bt -> Bt ’&’ Bs => ’&’
// -> Bs ;
void Bt()
{
    Bs();
    while (next_token.value == "&")
    {
        Read("&");
        Bs();
        Build_tree("&", 2);
    }
}

// Bs -> ’not’ Bp => ’not’
// -> Bp ;
void Bs()
{
    if (next_token.value == "not")
    {
        Read("not");
        Bp();
        Build_tree("not", 1);
    }
    else
    {
        Bp();
    }
}

// Bp -> A (’gr’ | ’>’ ) A => ’gr’
// -> A (’ge’ | ’>=’) A => ’ge’
// -> A (’ls’ | ’<’ ) A => ’ls’
// -> A (’le’ | ’<=’) A => ’le’
// -> A ’eq’ A => ’eq’
// -> A ’ne’ A => ’ne’
// -> A ;
void Bp()
{
    A();
    if ((next_token.value == "gr") || next_token.value == ">")
    {
        Read(next_token.value);
        A();
        Build_tree("gr", 2);
    }
    else if ((next_token.value == "ge") || next_token.value == ">=")
    {
        Read(next_token.value);
        A();
        Build_tree("ge", 2);
    }
    else if ((next_token.value == "ls") || next_token.value == "<")
    {
        Read(next_token.value);
        A();
        Build_tree("ls", 2);
    }
    else if ((next_token.value == "le") || next_token.value == "<=")
    {
        Read(next_token.value);
        A();
        Build_tree("le", 2);
    }
    else if (next_token.value == "eq")
    {
        Read(next_token.value);
        A();
        Build_tree("eq", 2);
    }
    else if (next_token.value == "ne")
    {
        Read(next_token.value);
        A();
        Build_tree("ne", 2);
    }
}

// A -> A ’+’ At => ’+’
// -> A ’-’ At => ’-’
// -> ’+’ At
// -> ’-’ At => ’neg’
// -> At ;
void A()
{

    if (next_token.value == "+")
    {
        Read("+");
        At();
    }
    else if (next_token.value == "-")
    {
        Read("-");
        At();
        Build_tree("neg", 1);
    }
    else
    {
        At();
    }
    while (next_token.value == "-" || next_token.value == "+")
    {
        string op = next_token.value;
        Read(op);
        At();
        Build_tree(op, 2);
    }
}

// At -> At ’*’ Af => ’*’
// -> At ’/’ Af => ’/’
// -> Af ;
void At()
{
    Af();
    while (next_token.value == "*" || next_token.value == "/")
    {
        string op = next_token.value;
        Read(op);
        Af();
        Build_tree(op, 2);
    }
}

// Af -> Ap ’**’ Af => ’**’
// -> Ap ;
void Af()
{
    Ap();
    if (next_token.value == "**")
    {
        Read("**");
        Af();
        Build_tree("**", 2);
    }
}

// Ap -> Ap ’@’ ’<IDENTIFIER>’ R => ’@’
// -> R ;
void Ap()
{
    R();
    while (next_token.value == "@")
    {
        Read("@");
        nodeStack.push(new Node(next_token.value, next_token.type));
        Read(next_token.value);
        R();
        Build_tree("@", 3);
    }
}

// R -> R Rn => ’gamma’
// -> Rn ;
void R()
{
    Rn();
    while ((next_token.type == IDENTIFIER && !isKeyWord(next_token.value)) || next_token.type == INTEGER || next_token.type == STRING ||
           (next_token.value == "true") || (next_token.value == "false") || (next_token.value == "nil") ||
           next_token.value == "(" || next_token.value == "dummy")
    {
        Rn();
        Build_tree("gamma", 2);
    }
}

// Rn -> ’<IDENTIFIER>’
// -> ’<INTEGER>’
// -> ’<STRING>’
// -> ’true’ => ’true’
// -> ’false’ => ’false’
// -> ’nil’ => ’nil’
// -> ’(’ E ’)’
// -> ’dummy’ => ’dummy’ ;
void Rn()
{
    if ((next_token.type == IDENTIFIER && !isKeyWord(next_token.value)) || next_token.type == INTEGER || next_token.type == STRING)
    {
        nodeStack.push(new Node(next_token.value, next_token.type));
        Read(next_token.value);
    }
    else if (next_token.value == "(")
    {
        Read("(");
        E();
        Read(")");
    }
    else if (next_token.value == "true")
    {
        Read("true");
        Build_tree("true", 0);
    }
    else if (next_token.value == "false")
    {
        Read("false");
        Build_tree("false", 0);
    }
    else if (next_token.value == "nil")
    {
        Read("nil");
        Build_tree("nil", 0);
    }
    else
    {
        Read("dummy");
        Build_tree("dummy", 0);
    }
}

// D -> Da ’within’ D => ’within’
// -> Da ;
void D()
{
    Da();
    if (next_token.value == "within")
    {
        Read("within");
        D();
        Build_tree("within", 2);
    }
}

// Da -> Dr ( ’and’ Dr )+ => ’and’
// -> Dr ;
void Da()
{
    Dr();
    int n = 0;
    while (next_token.value == "and")
    {
        n++;
        Read("and");
        Dr();
    }
    if (n > 0)
    {
        Build_tree("and", n + 1);
    }
}

// Dr -> ’rec’ Db => ’rec’
// -> Db ;
void Dr()
{
    if (next_token.value == "rec")
    {
        Read("rec");
        Db();
        Build_tree("rec", 1);
    }
    else
    {
        Db();
    }
}

// Db -> Vl ’=’ E => ’=’
// -> ’<IDENTIFIER>’ Vb+ ’=’ E => ’fcn_form’
// -> ’(’ D ’)’ ;
void Db()
{
    if (next_token.value == "(")
    {
        Read("(");
        D();
        Read(")");
    }
    else if (next_token.type == IDENTIFIER && !isKeyWord(next_token.value))
    {
        nodeStack.push(new Node(next_token.value, next_token.type));
        Read(next_token.value);
        if (next_token.value == "," || next_token.value == "=")
        {
            Vl();
            Read("=");
            E();
            Build_tree("=", 2);
        }
        else
        {
            int n = 0;
            while (next_token.value == "(" || (next_token.type == IDENTIFIER && !isKeyWord(next_token.value)))
            {
                n++;
                Vb();
            }
            Read("=");
            E();
            Build_tree("fcn_form", n + 2);
        }
    }
}

// Vl -> ’<IDENTIFIER>’ list ’,’ => ’,’?;
void Vl()
{
    int n = 1;
    while (next_token.value == ",")
    {
        n++;
        Read(",");
        Read(next_token.value);
    }

    if (n > 1)
    {
        Build_tree(",", n);
    }
}

// Vb -> ’<IDENTIFIER>’
// -> ’(’ Vl ’)’
// -> ’(’ ’)’ => ’()’;
void Vb()
{
    if ((next_token.type == IDENTIFIER && !isKeyWord(next_token.value)))
    {
        nodeStack.push(new Node(next_token.value, next_token.type));
        Read(next_token.value);
    }
    else if (next_token.value == "(")
    {
        Read("(");
        if (next_token.value == ")")
        {
            Read(")");
            Build_tree("()", 2);
        }
        else
        {
            Vl();
            Read(")");
        }
    }
}

void print_tree(Node *node, int indent = 0)
{
    if (!node)
        return;
    for (int i = 0; i < indent; i++)
        cout << ".";
    if (node->type == NAN)
    {
        cout << node->value << endl;
    }
    else
    {
        if (node->type == IDENTIFIER)
            cout << "<ID:" << node->value << ">" << endl;
        else if (node->type == INTEGER)
            cout << "<INT:" << node->value << ">" << endl;
        else if (node->type == STRING)
            cout << "<STR:'" << node->value << "'>" << endl;
    }
    print_tree(node->left, indent + 1);
    print_tree(node->right, indent);
}

void printAST(Node *node)
{
    print_tree(node);
}

Node *getAST(string filename)
{
    tokens = tokenizeFile(filename);

    Token token = tokens[token_index++];

    if (token.type == IDENTIFIER)
    {
        if ((token.value == "let" || token.value == "fn") && isKeyWord(token.value))
        {
            next_token = token;
        }
    }
    else
    {
        cout << "Error: unexpected token" << endl;
        exit(1);
    }

    E();

    Node *root = nodeStack.top();

    return root;
}
