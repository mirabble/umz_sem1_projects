#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

using namespace std;

std::unordered_set<std::string> dict = {
    "my", "you", "is", "Our", "book", "Iran", "university",
    "Babolsar", "need", "several", "study", "computer",
    "program", "black", "brown", "text", "Babol", "project",
    "write", "listen", "please", "block", "pay", "love",
    "like", "life", "favorite", "every", "day", "even", "odd",
    "save", "word", "other", "course", "Amol", "auto", "or",
    "member", "count", "total", "attempt", "which", "case",
    "when", "whose", "this", "how", "well", "user", "use",
    "can", "should", "will", "test", "type", "most", "must",
    "before", "start", "end", "your", "more", "most",
    "break", "machine", "small", "to", "modify", "change",
    "the", "student", "teacher", "only", "lonely", "with",
    "make", "technique", "no", "in"};

double levenshtein_distance(string word1, string word2)
{
    int size1 = word1.size();
    int size2 = word2.size();
    int verif[size1 + 1][size2 + 1];
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;
    for (int i = 0; i <= size1; i++)
        verif[i][0] = i;
    for (int j = 0; j <= size2; j++)
        verif[0][j] = j;
    for (int i = 1; i <= size1; i++)
    {
        for (int j = 1; j <= size2; j++)
        {
            int cost = (word2[j - 1] == word1[i - 1]) ? 0 : 1;
            verif[i][j] = min(
                min(verif[i - 1][j] + 1, verif[i][j - 1] + 1),
                verif[i - 1][j - 1] + cost);
        }
    }
    double sim = 1 - ((double)verif[size1][size2] / max(size1, size2));
    return sim;
}

int main()
{
    string inp = "In this smal project you nead to hang or modify the prog";
    stringstream words(inp);
    string word;
    while (words >> word)
    {
        string correct_word;
        if (dict.find(word) != dict.end())
            correct_word = word;
        else
        {
            double max_similarity = -1;
            for (string dict_word : dict)
            {
                double lev_score = levenshtein_distance(word, dict_word);
                if (lev_score > max_similarity)
                {
                    max_similarity = lev_score;
                    correct_word = dict_word;
                }
            }
        }
        cout << correct_word << " ";
    }
}
