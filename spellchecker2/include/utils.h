#pragma once
#include "Dictionary.h"
#include "Tokenizer.h"

using namespace std;

vector<Token> correctText(const vector<Token> &tokens, const Dictionary &dict);
string preserveCase(const string &original, const string &corrected);