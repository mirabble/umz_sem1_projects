#include <iostream>
#include "Tokenizer.h"
#include "Dictionary.h"
#include "EditDistance.h"
#include "utils.h"
#include <string>

using namespace std;

int main()
{
    string input;
    getline(cin, input)
    auto tokens = tokenize(input);
    Dictionary dict;

    cout << detokenize(tokens) << endl;

    for (auto &token : tokens)
    {
        if (token.type == TokenType::Word)
        {
            if (!dict.contains(token.text))
            {
                cout << "Misspelled: " << token.text << " -> " << findClosest(dict, token.text) << "\n";
            }
        }
    }

    auto correctedTokens = correctText(tokens, dict);
    auto output = detokenize(correctedTokens);
    cout << "Corrected Output : " << output << endl;
}
