#pragma once

#include <string>
#include <vector>

enum class TokenType
{
    Word,
    Punctuation,
    Whitespace
};

struct Token
{
    TokenType type;
    std::string text;
};

// helper function declarations
bool isLetter(char c);
bool isPunctuation(char c);
bool isWhitespace(char c);

// tokenizer interface
Token createToken(std::string s);
std::vector<Token> tokenize(const std::string &input);
std::string detokenize(std::vector<Token> tokens);