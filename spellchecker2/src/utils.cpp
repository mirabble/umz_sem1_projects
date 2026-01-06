#include "utils.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "Tokenizer.h"
#include <string>
#include <algorithm>

using namespace std;

string preserveCase(const string &original, const string &corrected)
{
    if (original.empty())
        return corrected;

    if (all_of(original.begin(), original.end(), ::isupper))
    {
        string upper = corrected;
        transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return upper;
    }

    if (isupper(original[0]))
    {
        string result = corrected;
        result[0] = toupper(result[0]);
        transform(result.begin() + 1, result.end(), result.begin() + 1, ::tolower);
        return result;
    }

    string lower = corrected;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

vector<Token> correctText(const vector<Token> &tokens, const Dictionary &dict)
{
    vector<Token> corrected;

    for (const auto &token : tokens)
    {
        if (token.type == TokenType::Word)
        {
            if (dict.contains(token.text))
            {
                corrected.push_back(token);
            }
            else
            {
                string best = findClosest(dict, token.text);
                corrected.push_back({TokenType::Word, preserveCase(token.text, best)});
            }
        }
        else
        {
            corrected.push_back(token);
        }
    }

    return corrected;
}
