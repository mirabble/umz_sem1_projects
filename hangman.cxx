#include <bits/stdc++.h>
using namespace std;

/* sample board
____  Hangman
|  |
|  O
| /|\
| / \
|___  _._._._._._._
Enter your Guess :
*/

void print_frame(string word, unsigned short int wrong_guesses, unordered_set<char> found_letters, unsigned short int error_code)
{
    system("clear");
    cout << "____  Hangman" << endl;
    cout << "|  |" << endl;
    cout << "|  " << (wrong_guesses >= 1 ? "O" : " ") << endl;
    cout << "| " << (wrong_guesses >= 3 ? "/" : " ") << (wrong_guesses >= 2 ? "|" : " ") << (wrong_guesses >= 4 ? "\\" : " ") << endl;
    cout << "| " << (wrong_guesses >= 5 ? "/" : " ") << " " << (wrong_guesses >= 6 ? "\\" : " ") << endl;
    cout << "|___   ";
    for (char letter : word)
    {
        if (found_letters.find(letter) != found_letters.end())
        {
            cout << letter;
        }
        else
        {
            cout << "-";
        }
    }
    cout << endl;
    switch (error_code)
    {
    case 1:
        cout << "You Guess didn't exist in the word !";
        break;
    case 2:
        cout << "You Already Guessed this letter !";
        break;
    }
}

bool check_letter_in_word(char letter, string word)
{
    for (char l : word)
    {
        if (l == letter)
        {
            return true;
        }
    }
    return false;
}

bool check_win_condition(string word, unordered_set<char> guessed_letters)
{
    unsigned short int word_size = word.length();
    unsigned short int count = 0;
    for (char l : word)
    {
        if (guessed_letters.find(l) != guessed_letters.end())
            count++;
    }
    return word_size == count;
}

int main()
{
    string word = "hangman";
    unordered_set<char> found_letters = {};
    unsigned short int guesses = 0;
    unsigned short int state = 0; // 0. Ok, 1. Wrong, 2. Already Guessed, 3. Lose, 4. Win
    while (true)
    {
        print_frame(word, guesses, found_letters, state);
        state = 0;
        cout << "\nEnter Your Guess : ";
        char guess;
        cin >> guess;
        if (guesses >= 6)
        {
            cout << "Lost !\nThe Word was " << word << " !\n";
            return 0;
        }
        if (found_letters.find(guess) != found_letters.end())
        {
            state = 2;
            found_letters.insert(guess);
            continue;
        }
        else if (!check_letter_in_word(guess, word))
        {
            state = 1;
            guesses += 1;
            found_letters.insert(guess);
            continue;
        }
        found_letters.insert(guess);
        if (check_win_condition(word, found_letters))
        {
            cout << "Victory !\n";
            return 0;
        }
    }
}