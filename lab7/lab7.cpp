
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct gl
{
	bool g;
	bool l;
};

vector <bool> gen_word();
void seeword();
void sortingdictionary();
void to_the_end();
gl recursive_func(string, vector <bool>, int, int);
void matching_search(vector <vector <bool>>, vector <bool>);
void gap_search(vector <vector <bool>>, vector <bool>, vector <bool>);
vector<vector<bool>> setofw = { {0,1,0,0,1,0,1,0},
{0,1,0,0,1,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,1},
{0,1,1,1,1,0,1,0},
{0,0,0,1,0,0,1,0},
{1,0,0,0,1,0,0,0},
{0,1,1,1,1,0,0,0},
{1,0,0,1,0,0,1,1},
{0,0,1,1,0,1,1,0},
{0,0,1,0,1,1,0,0},
{0,0,1,1,0,0,0,0},
{1,0,0,0,1,1,0,0},
{0,0,1,0,0,1,0,0},
{0,0,0,1,0,0,0,1},
{0,1,0,1,1,0,0,1},
{1,0,1,0,0,1,0,0},
{0,1,0,0,1,1,0,0},
{0,0,0,0,1,1,1,0},
{1,0,1,1,0,0,0,0} };
int main()
{
	cout << "Start dictionary:\n";
	seeword();
	system("pause");
	system("cls");
	sortingdictionary();
	cout << "Sorted dictionary (increasing):\n";
	seeword();
	system("pause");
	system("cls");
	to_the_end();
	cout << "Sorted dictionary (decreasing):\n";
	seeword();
}


void sortingdictionary() {
	setofw = { {0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,0},
	{0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,1,0},
	{0,0,0,1,0,0,1,1},
	{0,0,1,0,0,1,0,0},
	{0,0,1,0,1,1,0,0},
	{0,0,1,1,0,0,0,0},
	{0,0,1,1,0,1,1,0},
	{0,1,0,0,1,0,0,0},
	{0,1,0,0,1,0,1,0},
	{0,1,0,0,1,1,0,0},
	{0,1,0,1,1,0,0,1},
	{0,1,1,1,1,0,0,0},
	{0,1,1,1,1,0,1,0},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,1,0,0},
	{1,0,0,1,0,0,1,1},
	{1,0,1,0,0,1,0,0},
	{1,0,1,1,0,0,0,0} };


}

void to_the_end() {
	vector<bool> temp;
	for (int i = 0; i < 10; i++) {
		temp = setofw[i];
		setofw[i] = setofw[19 - i];
		setofw[19 - i] = temp;
	}
}

void seeword() {
	for (int i = 0; i < 20; i++) {
		cout << '[' << i + 1 << "] = ";
		for (int j = 0; j < 8; j++) {
			cout << setofw[i][j];
		}
		cout << endl;
	}
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