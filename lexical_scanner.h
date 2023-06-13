#ifndef LEXICAL_SCANNER_H
#define LEXICAL_SCANNER_H

#include <string>
#include <vector>
using namespace std;

// Define an enum to represent the different types of tokens
enum TokenType
{
    IDENTIFIER, // 0
    INTEGER,    // 1
    OPERATOR,   // 2
    STRING,     // 3
    DELETE,     // 4
    PUNCTION,   // 5
    NAN         // 6
};

// Define a struct to represent a token
struct Token
{
    TokenType type; // The type of the token
    string value;   // The value of the token
};

// Function to tokenize the contents of a file and return a vector of tokens
vector<Token> tokenizeFile(string fileName);

#endif
