#include <iostream>
#include <vector>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

struct WordComparison
{
    bool greater;
    bool lesser;
};

vector<bool> generateWord();
WordComparison recursiveFunction(string, vector<bool>, int, int);
void searchForMatches(vector<vector<bool>>, vector<bool>);
void searchWithGap(vector<vector<bool>>, vector<bool>, vector<bool>);

int main()
{
    srand(time(0));
    size_t count = 0;
    vector<vector<bool>> book;
    for (size_t eachWord = 0; eachWord < 50; eachWord++)
    {
        vector<bool> buffer = generateWord();
        book.push_back(buffer);
        cout << "[" << eachWord << "] ";
        for (size_t eachLetter = 0; eachLetter < buffer.size(); eachLetter++)
        {
            cout << buffer[eachLetter];
        }
        cout << endl;
    }
    cout << endl;

    string word;
    size_t mask;
    cout << "Enter a word to search: ";
    cin >> word;
    cout << "Enter mask: ";
    cin >> mask;
    for (size_t eachWord = 0; eachWord < book.size(); eachWord++)
    {
        WordComparison temp = recursiveFunction(word, book[eachWord], 0, mask);
        cout << "[" << eachWord << "] " << temp.greater << " " << temp.lesser << endl;
    }

    size_t number;
    cout << endl << "Enter a number of word: ";
    cin >> number;
    searchForMatches(book, book[number]);
    cout << endl;
    size_t high;
    size_t low;

    cout << "Enter higher & lower border words numbers: " << endl;
    cin >> high;
    cin >> low;
    searchWithGap(book, book[high], book[low]);

    system("pause");
    return 0;
}

vector<bool> generateWord()
{
    std::vector<bool> output;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1);
    for (size_t i = 0; i < 10; ++i)
    {
        output.push_back(distribution(gen));
    }

    return output;
}

WordComparison recursiveFunction(string arg, vector<bool> word, int iter, int mask)
{
    WordComparison temis;
    WordComparison temies1;
    if (iter + 1 == static_cast<int>(word.size()) - mask)
    {
        temies1.greater = false;
        temies1.lesser = false;
    }
    else
    {
        temies1 = recursiveFunction(arg, word, iter + 1, mask);
    }

    if (temies1.greater || (arg[iter] == '0' && word[iter] == 1 && !temies1.lesser))
    {
        temis.greater = true;
    }
    else
    {
        temis.greater = false;
    }

    if (temies1.lesser || (arg[iter] == '1' && word[iter] == 0 && !temies1.greater))
    {
        temis.lesser = true;
    }
    else
    {
        temis.lesser = false;
    }

    return temis;
};

void searchForMatches(vector<vector<bool>> book, vector<bool> word)
{
    vector<vector<bool>> bestMatches;
    vector<size_t> bestMatchNumbers;
    size_t bestMatchDischarge = 0;
    size_t currentBestMatchDischarge;
    for (size_t eachWord = 0; eachWord < book.size(); eachWord++)
    {
        if (word != book[eachWord])
        {
            currentBestMatchDischarge = 0;
            for (size_t eachLetter = 0; eachLetter < word.size(); eachLetter++)
            {
                if (word[eachLetter] == book[eachWord][eachLetter])
                {
                    currentBestMatchDischarge = eachLetter + 1;
                }
                else
                {
                    eachLetter = book[eachWord].size() + 1;
                }
            }
            if (currentBestMatchDischarge > bestMatchDischarge)
            {
                bestMatchDischarge = currentBestMatchDischarge;
                bestMatchNumbers.clear();
                bestMatches.clear();
                bestMatchNumbers.push_back(eachWord);
                bestMatches.push_back(book[eachWord]);
            }
            else if (currentBestMatchDischarge == bestMatchDischarge)
            {
                bestMatchNumbers.push_back(eachWord);
                bestMatches.push_back(book[eachWord]);
            }
        }
    }

    for (size_t eachWord = 0; eachWord < bestMatches.size(); eachWord++)
    {
        cout << "[" << bestMatchNumbers[eachWord] << "] ";
        for (size_t eachLetter = 0; eachLetter < bestMatches[eachWord].size(); eachLetter++)
        {
            cout << bestMatches[eachWord][eachLetter];
        }
        cout << endl;
    }

    cout << "Max matches searched: " << bestMatchDischarge << endl;
}

void searchWithGap(vector<vector<bool>> book, vector<bool> high, vector<bool> low)
{
    for (size_t eachWord = 0; eachWord < book.size(); eachWord++)
    {
        string times = "";
        for (size_t eachLetter = 0; eachLetter < book[eachWord].size(); eachLetter++)
        {
            times += to_string(book[eachWord][eachLetter]);
        }
        if (recursiveFunction(times, high, 0, 9).greater == 1 &&
            recursiveFunction(times, low, 0, 9).lesser == 0)
        {
            cout << "[" << eachWord << "] ";
            for (size_t iter = 0; iter < book[eachWord].size(); iter++)
            {
                cout << book[eachWord][iter];
            }
            cout << endl;
        }
    }
}