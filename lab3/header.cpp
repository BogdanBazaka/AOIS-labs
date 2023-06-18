#include "Header.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

std::vector<std::string> fragmentAND(std::string sourceString) {
	std::vector<std::string> result;
	std::string delimiter = "*";
	size_t pos = 0;

	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		std::string token = sourceString.substr(0, pos);
		result.push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}

	if (!sourceString.empty()) {
		result.push_back(sourceString);
	}

	return result;
}

std::vector<std::string> fragmentAND2(std::string sourceString) {
	std::vector<std::string> result;
	std::string delimiter = ")";
	size_t pos = 0;

	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		std::string token = sourceString.substr(1, pos - 1);
		result.push_back(token);
		sourceString.erase(0, pos + delimiter.length() + 1);
	}

	return result;
}

std::string checkAreNeighboursSDNF(std::string s1, std::string s2) {
	std::vector<std::string> a = fragmentAND(s1);
	std::vector<std::string> b = fragmentAND(s2);
	std::string minNeighboursResult = "";
	int k = 0;

	for (const std::string& strA : a) {
		bool isNeighbourFound = false;

		for (const std::string& strB : b) {
			if (strA == strB) {
				isNeighbourFound = true;

				if (minNeighboursResult.empty()) {
					minNeighboursResult += strA;
				}
				else {
					minNeighboursResult += "*" + strA;
				}

				break;
			}
		}

		if (!isNeighbourFound) {
			k++;

			if (k > 1) {
				return "";
			}
		}
	}

	return minNeighboursResult;
}


std::vector<std::string> fragmentationOR(std::string sourceString) {
	if (sourceString[0] == '(') {
		sourceString = sourceString.substr(1, sourceString.length() - 2);
	}

	std::vector<std::string> fragments;
	std::string delimiter = "+";
	size_t pos = 0;

	while ((pos = sourceString.find(delimiter)) != std::string::npos) {
		std::string token = sourceString.substr(0, pos);
		fragments.push_back(token);
		sourceString.erase(0, pos + delimiter.length());
	}

	if (!sourceString.empty()) {
		fragments.push_back(sourceString);
	}

	return fragments;
}


std::string gluingSDNF(std::string sourceString) {
	std::string resultOfGluing = "";
	std::vector<std::string> fragments = fragmentationOR(sourceString);

	for (int i = 0; i < fragments.size(); i++) {
		for (int j = i + 1; j < fragments.size(); j++) {
			std::string neighboursResult = checkAreNeighboursSDNF(fragments[i], fragments[j]);

			if (!neighboursResult.empty()) {
				if (resultOfGluing.empty()) {
					resultOfGluing += neighboursResult;
				}
				else {
					resultOfGluing += "+" + neighboursResult;
				}
			}
		}
	}

	return resultOfGluing;
}

std::string reverse(std::string sourceString) {
	if (sourceString[0] == '!') {
		return sourceString.substr(1);
	}
	else {
		return "!" + sourceString;
	}
}

bool find(const std::vector<std::string> sourceString, const std::string stringToFind) {
	for (const std::string str : sourceString) {
		if (str == stringToFind) {
			return true;
		}
	}
	return false;
}

bool checkExcess(const std::vector<std::string> sourceConstituents, int q) {
	std::vector<std::vector<std::string>> fragmentedConstituents;
	std::vector<std::string> fragmentsAnalyzingVector;

	for (const std::string& constituent : sourceConstituents) {
		std::vector<std::string> fragments = fragmentAND(constituent);
		fragmentedConstituents.push_back(fragments);
	}

	std::vector<std::string> k = fragmentedConstituents[q];

	for (int i = 0; i < k.size(); i++) {
		for (int j = 0; j < fragmentedConstituents.size(); j++) {
			if (j != q && find(fragmentedConstituents[j], reverse(k[i]))) {
				fragmentedConstituents.erase(fragmentedConstituents.begin() + j);
			}
		}
	}

	for (int i = 0; i < fragmentedConstituents.size(); i++) {
		if (i != q) {
			for (int j = 0; j < fragmentedConstituents[i].size(); j++) {
				if (!find(k, fragmentedConstituents[i][j])) {
					fragmentsAnalyzingVector.push_back(fragmentedConstituents[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < fragmentsAnalyzingVector.size(); i++) {
		if (!find(fragmentsAnalyzingVector, reverse(fragmentsAnalyzingVector[i]))) {
			return false;
		}
	}

	return true;
}


std::string toTDF(std::string sourceString) {
	std::vector<std::string> r = fragmentationOR(sourceString);

	for (int i = 0; i < r.size(); i++) {
		if (checkExcess(r, i)) {
			size_t pos = sourceString.find(r[i]);
			sourceString.erase(pos, r[i].length() + 1);
		}
	}

	return sourceString;
}

std::string checkAreNeighboursSKNF(const std::string s1, const std::string s2) {
	std::vector<std::string> a = fragmentationOR(s1);
	std::vector<std::string> b = fragmentationOR(s2);
	std::string ret = "(";
	int k = 0;

	for (const std::string& fragmentA : a) {
		bool foundMatch = false;

		for (const std::string& fragmentB : b) {
			if (fragmentA == fragmentB) {
				foundMatch = true;
				break;
			}
		}

		if (foundMatch) {
			if (ret != "(") {
				ret += "+";
			}
			ret += fragmentA;
		}
		else {
			k++;
		}

		if (k > 1) {
			return "";
		}
	}

	ret += ")";
	return ret;
}

std::string gluingSKNF(const std::string sourceString) {
	std::string gluingResult = "";
	std::vector<std::string> fragments = fragmentAND2(sourceString);

	for (int i = 0; i < fragments.size(); i++) {
		for (int j = i + 1; j < fragments.size(); j++) {
			std::string neighbours = checkAreNeighboursSKNF(fragments[i], fragments[j]);

			if (!neighbours.empty()) {
				if (!gluingResult.empty()) {
					gluingResult += "*";
				}

				gluingResult += neighbours;
			}
		}
	}

	return gluingResult;
}

bool checkExcess2(const std::vector<std::string> s, int q) {
	std::vector<std::vector<std::string>> r;
	std::vector<std::string> d;

	for (const std::string& source : s) {
		std::vector<std::string> t = fragmentationOR(source);
		r.push_back(t);
	}

	std::vector<std::string> k = r[q];

	for (int i = 0; i < k.size(); i++) {
		for (int j = 0; j < r.size(); j++) {
			if (j != q) {
				if (find(r[j], reverse(k[i]))) {
					r.erase(r.begin() + j);
				}
			}
		}
	}

	for (int i = 0; i < r.size(); i++) {
		if (i != q) {
			for (int j = 0; j < r[i].size(); j++) {
				if (!find(k, r[i][j])) {
					d.push_back(r[i][j]);
				}
			}
		}
	}

	for (int i = 0; i < d.size(); i++) {
		if (find(d, reverse(d[i]))) {
			return true;
		}
	}

	return false;
}


std::string toTKF(std::string sourceString) {
	std::vector<std::string> r = fragmentAND2(sourceString);
	for (int i = 0; i < r.size(); i++) {
		if (checkExcess2(r, i)) {
			sourceString.erase(sourceString.find(r[i]), r[i].length() + 3);
		}
	}
	return sourceString;
}

bool isInclude(const std::string s1, const std::string s2) {
	std::vector<std::string> v = fragmentAND(s1);
	for (const std::string& fragment : v) {
		if (fragment.length() == 2) {
			if (s2.find("*" + fragment) == std::string::npos && s2.find("+" + fragment) == std::string::npos && s2.find(fragment) != 0) {
				return false;
			}
		}
		else {
			if (s2.find(fragment) == std::string::npos) {
				return false;
			}
		}
	}
	return true;
}


std::string MCClassSDNF(const std::string SDNF, std::string DNF) {
	std::vector<std::string> fragmentedSDNF = fragmentationOR(SDNF);
	std::vector<std::string> fragmentedDNF = fragmentationOR(DNF);
	std::vector<std::vector<char>> table(fragmentedDNF.size(), std::vector<char>(fragmentedSDNF.size()));

	for (int i = 0; i < fragmentedDNF.size(); i++) {
		for (int j = 0; j < fragmentedSDNF.size(); j++) {
			if (isInclude(fragmentedDNF[i], fragmentedSDNF[j])) {
				table[i][j] = 'X';
			}
		}
	}

	for (int i = 0; i < fragmentedSDNF.size(); i++) {
		std::cout << "\t  " << fragmentedSDNF[i];
	}

	for (int i = 0; i < fragmentedDNF.size(); i++) {
		std::cout << std::endl;
		std::cout << fragmentedDNF[i] << "     ";
		for (int j = 0; j < fragmentedSDNF.size(); j++) {
			std::cout << table[i][j] << "\t\t     ";
		}
	}

	std::vector<std::string> preResult;
	for (int i = 0; i < fragmentedDNF.size(); i++) {
		bool u = false;
		for (int j = 0; j < fragmentedSDNF.size(); j++) {
			if (table[i][j] == 'X') {
				for (int k = 0; k < fragmentedDNF.size(); k++) {
					if (table[k][j] == 'X') {
						if (k != i) {
							break;
						}
					}
					else if (k + 2 == fragmentedDNF.size()) {
						u = true;
						break;
					}
				}
			}
			if (u) {
				break;
			}
		}
		if (!u) {
			preResult.push_back(fragmentedDNF[i]);
		}
	}

	for (int i = 0; i < preResult.size(); i++) {
		size_t pos = DNF.find(preResult[i]);
		if (pos != std::string::npos) {
			if (pos > 0 && DNF[pos - 1] == '!') {
				DNF.erase(pos - 1, preResult[i].length() + 2);
			}
			else {
				DNF.erase(pos, preResult[i].length() + 1);
			}
		}
	}

	return DNF;
}


bool isInclude2(const string s1, const string s2) {
	vector<string> v = fragmentationOR(s1);
	for (const string& fragment : v) {
		if (fragment.length() == 2) {
			if (s2.find("+" + fragment) == string::npos && s2.find(fragment) != 0)
				return false;
		}
		else {
			if (s2.find(fragment) == string::npos)
				return false;
		}
	}
	return true;
}


string MCClassSKNF(const string SKNF, string KNF) {
	vector<string> h = fragmentAND2(SKNF);
	vector<string> l = fragmentAND2(KNF);
	vector<vector<char>> table(l.size(), vector<char>(h.size()));

	for (int i = 0; i < l.size(); i++) {
		for (int j = 0; j < h.size(); j++) {
			if (isInclude2(l[i], h[j]))
				table[i][j] = 'X';
		}
	}

	for (const string& fragment : h) {
		cout << "\t  " << fragment;
	}

	for (int i = 0; i < l.size(); i++) {
		cout << '\n' << l[i] << "     ";
		for (int j = 0; j < h.size(); j++) {
			cout << table[i][j] << "\t\t     ";
		}
	}

	vector<string> r;
	for (int i = 0; i < l.size(); i++) {
		bool u = false;
		for (int j = 0; j < h.size(); j++) {
			if (table[i][j] == 'X') {
				for (int k = 0; k < l.size(); k++) {
					if (table[k][j] == 'X') {
						if (k != i)
							break;
					}
					else if (k + 2 == l.size()) {
						u = true;
						break;
					}
				}
			}
			if (u)
				break;
		}
		if (!u)
			r.push_back(l[i]);
	}

	for (const string& fragment : r) {
		if (!KNF.find(fragment))
			KNF.erase(0, fragment.length() + 1);
		else
			KNF.erase(KNF.find(fragment) - 1, fragment.length() + 3);
	}

	return KNF;
}


vector<vector<int>> makeDiagram(int countOfArguments) {
	int horizontalO;
	vector<vector<int>> diagram;
	if (countOfArguments % 2 == 0) {
		diagram.resize(pow(2, countOfArguments / 2));
		horizontalO = pow(2, countOfArguments / 2);
	}
	else {
		diagram.resize(pow(2, (countOfArguments - 1) / 2));
		horizontalO = pow(2, (countOfArguments + 1) / 2);
	}
	for (int i = 0; i < diagram.size(); i++) {
		vector<int> t(horizontalO);
		diagram[i] = t;
	}
	return diagram;
}

unsigned int GrayCode(unsigned int code) {
	return code ^ (code >> 1);
}

string twoten(int x, int n) {
	string k;
	int i = 0;
	long long c = 0;
	while (x != 0) {
		while (x - pow(2, i + 1) >= 0) {
			i++;
		}
		x -= pow(2, i);
		c += pow(10, i);
		i = 0;
	}
	k = to_string(c);
	while (k.length() < n) {
		k = '0' + k;
	}
	return k;
}

bool isInclude3(string s, string str) {
	vector<string> Str = fragmentationOR(str);
	for (int i = 0; i < Str.size(); i++) {
		if (isInclude(s, Str[i])) {
			return true;
		}
	}
	return false;
}


string FindTDF(string s1, string s2) {
	string d = "";
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] == '0' && s2[i] == '0')
			d += "*!x" + to_string(i + 1);
		if (s1[i] == '1' && s2[i] == '1')
			d += "*x" + to_string(i + 1);
	}
	d.erase(0, 1);
	return d;
}

vector<string> normal(vector<string> s) {
	vector<string> t;
	for (int i = 0; i < s.size(); i++) {
		if (!find(t, s[i]))
			t.push_back(s[i]);
	}
	for (int i = 0; i < t.size(); i++) {
		vector<string> fr = fragmentAND(t[i]);
		bool g = false;
		for (int k = 0; k < t.size() - 1; k++) {
			if (k != i) {
				if ((isInclude(fr[0], t[k]) && isInclude(fr[1], t[k + 1])) ||
					(isInclude(fr[1], t[k]) && isInclude(fr[0], t[k + 1]))) {
					t.erase(t.begin() + i);
					g = true;
					break;
				}
			}
		}
		if (g) {
			break;
		}
	}
	return t;
}

string WeichCarno(string SDNF, int countOfArguments) {
	vector<vector<int>> diagram = makeDiagram(countOfArguments);
	vector<string> v;
	vector<string> g;
	vector<string> answer;
	string TF;
	int horizontalO = (countOfArguments % 2 == 0) ? pow(2, countOfArguments / 2) : pow(2, (countOfArguments + 1) / 2);
	int verticalO = pow(2, countOfArguments - log2(horizontalO));
	for (int i = 0; i < verticalO; i++)
		v.push_back(twoten(GrayCode(i), log2(verticalO)));
	for (int i = 0; i < horizontalO; i++)
		g.push_back(twoten(GrayCode(i), log2(horizontalO)));
	for (int i = 0; i < diagram.size(); i++) {
		for (int j = 0; j < diagram[i].size(); j++) {
			string s = v[i] + g[j];
			string b = "";
			for (int k = 0; k < s.length(); k++) {
				if (s[k] == '0') {
					b += (b.empty()) ? "!x" + to_string(k + 1) : "*!x" + to_string(k + 1);
				}
				else {
					b += (b.empty()) ? "x" + to_string(k + 1) : "*x" + to_string(k + 1);
				}
			}
			diagram[i][j] = (isInclude3(b, SDNF)) ? 1 : 0;
		}
	}

	for (int i = 0; i < g.size(); i++) {
		cout << "\t" << g[i];
	}

	for (int i = 0; i < v.size(); i++) {
		cout << '\n' << v[i] << "      ";
		for (int j = 0; j < g.size(); j++) {
			cout << diagram[i][j] << "\t ";
		}
	}

	for (int i = 0; i < diagram.size(); i++) {
		for (int j = 0; j < diagram[i].size(); j++) {
			if (diagram[i][j] == 1) {
				if (i + 1 < diagram.size() && diagram[i + 1][j] == 1)
					answer.push_back(FindTDF(v[i] + g[j], v[i + 1] + g[j]));
				if (i - 1 >= 0 && diagram[i - 1][j] == 1)
					answer.push_back(FindTDF(v[i] + g[j], v[i - 1] + g[j]));
				if (j - 1 >= 0) {
					if (diagram[i][j - 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[j - 1]));
				}
				else {
					if (diagram[i][g.size() - 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[g.size() - 1]));
				}
				if (j + 1 < g.size()) {
					if (diagram[i][j + 1] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[j + 1]));
				}
				else {
					if (diagram[i][0] == 1)
						answer.push_back(FindTDF(v[i] + g[j], v[i] + g[0]));
				}
			}
		}
	}
	answer = normal(answer);

	for (int i = 0; i < diagram.size(); i++) {
		TF += "+" + answer[i];
	}

	TF.erase(0, 1);
	return TF;
}


bool isInclude4(string s, string str) {
	vector<string> fragments = fragmentAND2(str);
	for (int i = 0; i < fragments.size(); i++) {
		if (isInclude2(s, fragments[i])) {
			return true;
		}
	}
	return false;
}

string FindTKF(string s1, string s2) {
	string result = "(";
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] == '0' && s2[i] == '0') {
			result += "+x" + to_string(i + 1);
		}
		else if (s1[i] == '1' && s2[i] == '1') {
			result += "+!x" + to_string(i + 1);
		}
	}
	result.erase(1, 1);
	result += ")";
	return result;
}


vector<string> normal2(vector<string> s) {
	vector<string> t;
	for (int i = 0; i < s.size(); i++) {
		string substring = s[i].substr(1, s[i].length() - 2);
		if (!find(t, substring)) {
			t.push_back(substring);
		}
	}

	for (int i = 0; i < t.size(); i++) {
		vector<string> fragments = fragmentationOR(t[i]);
		bool foundMatch = false;
		int matchCount = 0;
		for (int k = 0; k < t.size(); k++) {
			if (k != i) {
				if (isInclude2(fragments[matchCount], t[k])) {
					matchCount++;
				}
			}
			if (matchCount == 2) {
				t.erase(t.begin() + i);
				foundMatch = true;
				break;
			}
		}
		if (foundMatch) {
			break;
		}
	}

	return t;
}

string WeichCarno2(string SKNF, int n) {
	vector<vector<int>> diagram = makeDiagram(n);
	vector<string> v;
	vector<string> g;
	vector<string> answer;
	string TF;
	int horizontalO;
	int verticalO;
	if (n % 2 == 0) {
		horizontalO = pow(2, n / 2);
		verticalO = pow(2, n / 2);
	}
	else {
		horizontalO = pow(2, (n + 1) / 2);
		verticalO = pow(2, (n - 1) / 2);
	}
	for (int i = 0; i < verticalO; i++)
		v.push_back(twoten(GrayCode(i), log2(verticalO)));
	for (int i = 0; i < horizontalO; i++)
		g.push_back(twoten(GrayCode(i), log2(horizontalO)));
	for (int i = 0; i < diagram.size(); i++)
	{
		for (int j = 0; j < diagram[i].size(); j++)
		{
			string s = v[i] + g[j];
			string b = "";
			for (int k = 0; k < s.length(); k++)
			{

				if (s[k] == '0')
				{
					if (b == "")
					{
						b += "x" + to_string(k + 1);
					}
					else
					{
						b += "+x" + to_string(k + 1);
					}
				}
				else
				{
					if (b == "")
					{
						b += "!x" + to_string(k + 1);
					}
					else
					{
						b += "+!x" + to_string(k + 1);
					}
				}
			}
			if (!isInclude4(b, SKNF))
				diagram[i][j] = 0;
			else
				diagram[i][j] = 1;
		}
	}
	for (int i = 0; i < g.size(); i++)
		cout << "\t" << g[i];
	for (int i = 0; i < v.size(); i++)
	{
		cout << '\n' << v[i] << "      ";
		for (int j = 0; j < g.size(); j++)
			cout << diagram[i][j] << "\t ";
	}
	for (int i = 0; i < diagram.size(); i++)
	{
		for (int j = 0; j < diagram[i].size(); j++)
		{
			if (!diagram[i][j])
			{
				if (i + 1 < diagram.size())
					if (!diagram[i + 1][j])
						answer.push_back(FindTKF(v[i] + g[j], v[i + 1] + g[j]));
				if (i - 1 >= 0)
					if (!diagram[i - 1][j])
						answer.push_back(FindTKF(v[i] + g[j], v[i - 1] + g[j]));
				if (j - 1 >= 0)
				{
					if (!diagram[i][j - 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[j - 1]));
				}
				else
				{
					if (!diagram[i][g.size() - 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[g.size() - 1]));
				}
				if (j + 1 < g.size())
				{
					if (!diagram[i][j + 1])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[j + 1]));
				}
				else
				{
					if (!diagram[i][0])
						answer.push_back(FindTKF(v[i] + g[j], v[i] + g[0]));
				}

			}
		}
	}
	answer = normal2(answer);
	for (int i = 0; i < diagram.size(); i++)
	{
		TF += ")*(" + answer[i];
	}
	TF.erase(0, 2);
	TF += ')';
	return TF;
}