#pragma once
#include <string>
#include <unordered_set>

using namespace std;

class Dictionary
{
public:
    Dictionary();

    bool contains(const string &word) const;
    unordered_set<string> getWords() const;

private:
    unordered_set<string> words;
    static string toLower(const string &s);
};

string findClosest(const Dictionary &dict, const string &word);