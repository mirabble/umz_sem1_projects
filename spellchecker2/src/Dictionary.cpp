#include "Dictionary.h"
#include "EditDistance.h"
#include <algorithm>
#include <limits>

using namespace std;

Dictionary::Dictionary()
{
    const char *dict[] = {
        "my", "in", "is", "our", "book", "iran", "university",
        "babolsar", "need", "several", "study", "computer",
        "program", "black", "brown", "text", "babol", "project",
        "write", "listen", "please", "block", "pay", "love",
        "like", "life", "favorite", "every", "day", "even", "odd",
        "save", "word", "other", "course", "amol", "auto", "or",
        "member", "count", "total", "attempt", "which", "read",
        "when", "whose", "this", "how", "well", "user", "use",
        "can", "should", "will", "test", "type", "most", "must",
        "before", "start", "end", "you", "more", "case",
        "break", "machine", "small", "to", "modify", "change",
        "the", "student", "teacher", "only", "lonely", "with",
        "make", "technique", "no"};

    for (auto w : dict)
        words.insert(w);
}

bool Dictionary::contains(const string &word) const
{
    return words.find(toLower(word)) != words.end();
}

unordered_set<string> Dictionary::getWords() const
{
    return words;
}

string Dictionary::toLower(const string &s)
{
    string result = s;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c)
              { return tolower(c); });
    return result;
}

string findClosest(const Dictionary &dict, const string &word)
{
    string bestMatch;
    int minScore = numeric_limits<int>::max();

    for (const auto &w : dict.getWords())
    {
        int editDistance = levenshtein(word, w);
        int lengthPenalty = labs(word.length() - w.length()) * 0.5;
        int score = editDistance + lengthPenalty;

        if (w.find(word) != string::npos)
            score -= 2;

        if (score < minScore)
        {
            minScore = score;
            bestMatch = w;
        }
    }
    return bestMatch;
}