#include "Tokenizer.h"
#include <cctype>

using namespace std;

bool isLetter(char c)
{
    return isalpha(static_cast<unsigned char>(c));
}

bool isPunctuation(char c)
{
    string p = ".,!?;:";
    return p.find(c) != string::npos;
}

bool isWhitespace(char c)
{
    return isspace(static_cast<unsigned char>(c));
}

Token createToken(string s)
{
    Token token;
    token.text = s;

    if (isPunctuation(s[0]))
    {
        token.type = TokenType::Punctuation;
    }
    else if (isWhitespace(s[0]))
    {
        token.type = TokenType::Whitespace;
    }
    else
    {
        token.type = TokenType::Word;
    }

    return token;
}

vector<Token> tokenize(const string &input)
{
    vector<Token> tokens;
    string buffer;

    for (char letter : input)
    {
        if (isLetter(letter))
        {
            buffer += letter;
        }
        else
        {
            if (!buffer.empty())
            {
                tokens.push_back(createToken(buffer));
                buffer.clear();
            }

            string s(1, letter);
            tokens.push_back(createToken(s));
        }
    }

    if (!buffer.empty())
    {
        tokens.push_back(createToken(buffer));
    }

    return tokens;
}

string detokenize(vector<Token> tokens)
{
    string text = "";
    for (Token t : tokens)
    {
        text += t.text;
    }
    return text;
}
