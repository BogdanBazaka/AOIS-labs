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

vector<bool> genWord();
WordComparison recursiveFunction(string, vector<bool>, int, int);
void searchForMatches(vector<vector<bool>>, vector<bool>);
void searchWithGap(vector<vector<bool>>, vector<bool>, vector<bool>);

int main()
{
    srand(time(0));
    size_t count = 0;
    vector<vector<bool>> boook;
    for (size_t iter = 0; iter < 50; iter++)
    {
        vector<bool> buffer = genWord();
        boook.push_back(buffer);
        cout << "[" << iter << "] ";
        for (size_t jiter = 0; jiter < buffer.size(); jiter++)
        {
            cout << buffer[jiter];
        }
        cout << endl;
    }
    cout << endl;

    string wordd;
    size_t msk;
    cout << "Enter a word to search: ";
    cin >> wordd;
    cout << "Enter mask: ";
    cin >> msk;
    for (size_t iter = 0; iter < boook.size(); iter++)
    {
        WordComparison temp = recursiveFunction(wordd, boook[iter], 0, msk);
        cout << "[" << iter << "] " << temp.greater << " " << temp.lesser << endl;
    }

    size_t number;
    cout << endl << "Enter a number of word: ";
    cin >> number;
    searchForMatches(boook, boook[number]);
    cout << endl;
    size_t higher;
    size_t lowest;

    cout << "Enter higher & lower border words numbers: " << endl;
    cin >> higher;
    cin >> lowest;
    searchWithGap(boook, boook[higher], boook[lowest]);

    system("pause");
    return 0;
}

WordComparison recursiveFunction(string args, vector<bool> woord, int iter, int msk)
{
    WordComparison temis;
    WordComparison temies1;
    if (iter + 1 == static_cast<int>(woord.size()) - msk)
    {
        temies1.greater = false;
        temies1.lesser = false;
    }
    else
    {
        temies1 = recursiveFunction(args, woord, iter + 1, msk);
    }

    if (temies1.greater || (args[iter] == '0' && woord[iter] == 1 && !temies1.lesser))
    {
        temis.greater = true;
    }
    else
    {
        temis.greater = false;
    }

    if (temies1.lesser || (args[iter] == '1' && woord[iter] == 0 && !temies1.greater))
    {
        temis.lesser = true;
    }
    else
    {
        temis.lesser = false;
    }

    return temis;
};

vector<bool> genWord()
{
    std::vector<bool> outp;
    std::random_device rdd;
    std::mt19937 gener(rdd());
    std::uniform_int_distribution<int> distrib(0, 1);
    for (size_t i = 0; i < 10; ++i)
    {
        outp.push_back(distrib(gener));
    }

    return outp;
}

void searchForMatches(vector<vector<bool>> boook, vector<bool> slovo)
{
    vector<vector<bool>> thebestM;
    vector<size_t> CountOfBestMatches;
    size_t DischargeTheBestM = 0;
    size_t BestMDischargeCurr;
    for (size_t iter = 0; iter < boook.size(); iter++)
    {
        if (slovo != boook[iter])
        {
            BestMDischargeCurr = 0;
            for (size_t jiter = 0; jiter < slovo.size(); jiter++)
            {
                if (slovo[jiter] == boook[iter][jiter])
                {
                    BestMDischargeCurr = jiter + 1;
                }
                else
                {
                    jiter = boook[iter].size() + 1;
                }
            }
            if (BestMDischargeCurr > DischargeTheBestM)
            {
                DischargeTheBestM = BestMDischargeCurr;
                CountOfBestMatches.clear();
                thebestM.clear();
                CountOfBestMatches.push_back(iter);
                thebestM.push_back(boook[iter]);
            }
            else if (BestMDischargeCurr == DischargeTheBestM)
            {
                CountOfBestMatches.push_back(iter);
                thebestM.push_back(boook[iter]);
            }
        }
    }

    for (size_t iter = 0; iter < thebestM.size(); iter++)
    {
        cout << "[" << CountOfBestMatches[iter] << "] ";
        for (size_t eachLetter = 0; eachLetter < thebestM[iter].size(); eachLetter++)
        {
            cout << thebestM[iter][eachLetter];
        }
        cout << endl;
    }

    cout << "Max matches searched: " << DischargeTheBestM << endl;
}

void searchWithGap(vector<vector<bool>> boook, vector<bool> higher, vector<bool> lowest)
{
    for (size_t iter = 0; iter < boook.size(); iter++)
    {
        string times = "";
        for (size_t jiter = 0; jiter < boook[iter].size(); jiter++)
        {
            times += to_string(boook[iter][jiter]);
        }
        if (recursiveFunction(times, higher, 0, 9).greater == 1 &&
            recursiveFunction(times, lowest, 0, 9).lesser == 0)
        {
            cout << "[" << iter << "] ";
            for (size_t iter = 0; iter < boook[iter].size(); iter++)
            {
                cout << boook[iter][iter];
            }
            cout << endl;
        }
    }
}