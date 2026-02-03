#pragma once
#include <string>
#include <vector>

using namespace std;

enum class TokenType
{
    Word,
    Punctuation,
    Whitespace
};

struct Token
{
    TokenType type;
    string text;
};

// helper function declarations
bool isLetter(char c);
bool isPunctuation(char c);
bool isWhitespace(char c);

// tokenizer interface
Token createToken(std::string s);
vector<Token> tokenize(const std::string &input);
string detokenize(std::vector<Token> tokens);
