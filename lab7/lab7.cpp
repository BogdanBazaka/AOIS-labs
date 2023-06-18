#include <iostream>
#include <vector>
#include <tchar.h>
#include <stdio.h>
#include <string>

using namespace std;

struct gl
{
	bool g;
	bool l;
};

vector <bool> gen_word();
gl recursive_func(string, vector <bool>, int, int);
void matching_search(vector <vector <bool>>, vector <bool>);
void gap_search(vector <vector <bool>>, vector <bool>, vector <bool>);


int main()
{
	size_t counter = 0;
	vector <vector <bool>> book;
	for (size_t each_word = 0; each_word < 50; each_word++)
	{
		vector <bool> boof = gen_word();
		book.push_back(boof);
		cout << "[" << each_word << "] ";
		for (size_t each_letter = 0; each_letter < boof.size(); each_letter++)
		{
			cout << boof[each_letter];
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
	for (size_t each_word = 0; each_word < book.size(); each_word++)
	{
		gl temp = recursive_func(word, book[each_word], 0, mask);
		cout << "[" << each_word << "] " << temp.g << " " << temp.l << endl;
	}

	size_t number;
	cout << endl << "Enter a number of word: ";
	cin >> number;
	matching_search(book, book[number]);
	cout << endl;
	size_t high;
	size_t low;

	cout << "Enter higher & lower border words numbers: " << endl;
	cin >> high;
	cin >> low;
	gap_search(book, book[high], book[low]);

	system("pause");
	return 0;
}

vector <bool> gen_word()
{
	vector <bool> out;
	for (size_t each_letter = 0; each_letter < 10; each_letter++)
	{
		if (rand() % 2 == 1)
		{
			out.push_back(1);
		}
		else
		{
			out.push_back(0);
		}
	}
	return out;
}
gl recursive_func(string argument, vector <bool> word, int i, int mask) {
	gl temp;
	gl temp1;
	if (i + 1 == word.size() - mask)
	{
		temp1.g = false;
		temp1.l = false;
	}
	else
	{
		temp1 = recursive_func(argument, word, i + 1, mask);
	}
	if (temp1.g || (argument[i] == '0' && word[i] == 1 && !temp1.l))
		temp.g = true;
	else
		temp.g = false;
	if (temp1.l || (argument[i] == '1' && word[i] == 0 && !temp1.g))
		temp.l = true;
	else
		temp.l = false;
	return temp;
};
void matching_search(vector <vector <bool>> book, vector <bool> word)
{
	vector <vector <bool>> best_matches;
	vector <size_t> best_mutch_numb;
	size_t best_mutch_discharge = 0;
	size_t current_best_mutch_discharge;

	for (size_t each_word = 0; each_word < book.size(); each_word++)
	{
		if (word != book[each_word])
		{
			current_best_mutch_discharge = 0;
			for (size_t each_letter = 0; each_letter < word.size(); each_letter++)
			{
				if (word[each_letter] == book[each_word][each_letter])
				{
					current_best_mutch_discharge = each_letter + 1;
				}
				else
				{
					each_letter = book[each_word].size() + 1;
				}
			}
			if (current_best_mutch_discharge > best_mutch_discharge)
			{
				best_mutch_discharge = current_best_mutch_discharge;
				best_mutch_numb.clear();
				best_matches.clear();
				best_mutch_numb.push_back(each_word);
				best_matches.push_back(book[each_word]);
			}
			else if (current_best_mutch_discharge == best_mutch_discharge)
			{
				best_mutch_numb.push_back(each_word);
				best_matches.push_back(book[each_word]);
			}
		}
	}

	for (size_t each_word = 0; each_word < best_matches.size(); each_word++)
	{
		cout << "[" << best_mutch_numb[each_word] << "] ";
		for (size_t each_letter = 0; each_letter < best_matches[each_word].size(); each_letter++)
		{
			cout << best_matches[each_word][each_letter];
		}
		cout << endl;
	}

	cout << "Max matches discharge: " << best_mutch_discharge << endl;
}
void gap_search(vector <vector <bool>> book, vector <bool> high, vector <bool> low)
{
	for (size_t each_word = 0; each_word < book.size(); each_word++)
	{
		string temp = "";
		for (size_t each_letter = 0; each_letter < book[each_word].size(); each_letter++)
		{
			temp += to_string(book[each_word][each_letter]);
		}
		if (recursive_func(temp, high, 0, 9).g == 1 &&
			recursive_func(temp, low, 0, 9).l == 0)
		{
			cout << "[" << each_word << "] ";
			for (size_t i = 0; i < book[each_word].size(); i++)
			{
				cout << book[each_word][i];
			}
			cout << endl;
		}
	}
}