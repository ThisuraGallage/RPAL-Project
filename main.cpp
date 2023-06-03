#include "lexical_scanner.h"
#include <iostream>
using namespace std;

int main()
{
    vector<Token> tokens = tokenizeFile("1.txt");
    for (int i = 0; i < tokens.size(); i++)
    {
        cout << "Token " << tokens[i].type << ": " << tokens[i].value << endl;
    }
    return 0;
}