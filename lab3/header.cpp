#include "Header.h"
#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

std::vector<std::string> fragmentAND(std::string source) {
	std::vector<std::string> res;
	std::string delim = "*";
	size_t pozition = 0;

	while ((pozition = source.find(delim)) != std::string::npos) {
		std::string coin = source.substr(0, pozition);
		res.push_back(coin);
		source.erase(0, pozition + delim.length());
	}

	if (!source.empty()) {
		res.push_back(source);
	}

	return res;
}

std::vector<std::string> fragmentAND2(std::string source) {
	std::vector<std::string> res;
	std::string delim = ")";
	size_t pozit = 0;

	while ((pozit = source.find(delim)) != std::string::npos) {
		std::string coin = source.substr(1, pozit - 1);
		res.push_back(coin);
		source.erase(0, pozit + delim.length() + 1);
	}

	return res;
}

std::string AreNeighSDNF(std::string string1, std::string string2) {
	std::vector<std::string> ad = fragmentAND(string1);
	std::vector<std::string> bd = fragmentAND(string2);
	std::string minimalNeighbsRes = "";
	int schet = 0;

	for (const std::string& strinA : ad) {
		bool isNeighbSeatched = false;

		for (const std::string& strinB : bd) {
			if (strinA == strinB) {
				isNeighbSeatched = true;

				if (minimalNeighbsRes.empty()) {
					minimalNeighbsRes += strinA;
				}
				else {
					minimalNeighbsRes += "*" + strinA;
				}

				break;
			}
		}

		if (!isNeighbSeatched) {
			schet++;

			if (schet > 1) {
				return "";
			}
		}
	}

	return minimalNeighbsRes;
}


std::vector<std::string> fragmentOR(std::string source) {
	if (source[0] == '(') {
		source = source.substr(1, source.length() - 2);
	}

	std::vector<std::string> frags;
	std::string delim = "+";
	size_t pozit = 0;

	while ((pozit = source.find(delim)) != std::string::npos) {
		std::string coin = source.substr(0, pozit);
		frags.push_back(coin);
		source.erase(0, pozit + delim.length());
	}

	if (!source.empty()) {
		frags.push_back(source);
	}

	return frags;
}


std::string gluiSDNF(std::string source) {
	std::string resOfGluin = "";
	std::vector<std::string> frags = fragmentOR(source);

	for (int iter = 0; iter < frags.size(); iter++) {
		for (int jiter = iter + 1; jiter < frags.size(); jiter++) {
			std::string neighbsRes = AreNeighSDNF(frags[iter], frags[jiter]);

			if (!neighbsRes.empty()) {
				if (resOfGluin.empty()) {
					resOfGluin += neighbsRes;
				}
				else {
					resOfGluin += "+" + neighbsRes;
				}
			}
		}
	}

	return resOfGluin;
}

std::string revers(std::string source) {
	if (source[0] == '!') {
		return source.substr(1);
	}
	else {
		return "!" + source;
	}
}

bool tofind(const std::vector<std::string> source, const std::string stringForFind) {
	for (const std::string strin : source) {
		if (strin == stringForFind) {
			return true;
		}
	}
	return false;
}

bool Excess(const std::vector<std::string> needConstituents, int z) {
	std::vector<std::vector<std::string>> fragConsts;
	std::vector<std::string> fragsAnalyzVec;

	for (const std::string& consts : needConstituents) {
		std::vector<std::string> frags = fragmentAND(consts);
		fragConsts.push_back(frags);
	}

	std::vector<std::string> ker = fragConsts[z];

	for (int iter = 0; iter < ker.size(); iter++) {
		for (int jiter = 0; jiter < fragConsts.size(); jiter++) {
			if (jiter != z && tofind(fragConsts[jiter], revers(ker[iter]))) {
				fragConsts.erase(fragConsts.begin() + jiter);
			}
		}
	}

	for (int iter = 0; iter < fragConsts.size(); iter++) {
		if (iter != z) {
			for (int jiter = 0; jiter < fragConsts[iter].size(); jiter++) {
				if (!tofind(ker, fragConsts[iter][jiter])) {
					fragsAnalyzVec.push_back(fragConsts[iter][jiter]);
				}
			}
		}
	}

	for (int iter = 0; iter < fragsAnalyzVec.size(); iter++) {
		if (!tofind(fragsAnalyzVec, revers(fragsAnalyzVec[iter]))) {
			return false;
		}
	}

	return true;
}


std::string TDFfunc(std::string source) {
	std::vector<std::string> rs = fragmentOR(source);

	for (int iter = 0; iter < rs.size(); iter++) {
		if (Excess(rs, iter)) {
			size_t pozit = source.find(rs[iter]);
			source.erase(pozit, rs[iter].length() + 1);
		}
	}

	return source;
}

std::string AreNeighSKNF(const std::string string1, const std::string string2) {
	std::vector<std::string> ag = fragmentOR(string1);
	std::vector<std::string> bg = fragmentOR(string2);
	std::string rat = "(";
	int t = 0;

	for (const std::string& fragmA : ag) {
		bool searchMatch = false;

		for (const std::string& fragmB : bg) {
			if (fragmA == fragmB) {
				searchMatch = true;
				break;
			}
		}

		if (searchMatch) {
			if (rat != "(") {
				rat += "+";
			}
			rat += fragmA;
		}
		else {
			t++;
		}

		if (t > 1) {
			return "";
		}
	}

	rat += ")";
	return rat;
}

std::string gluiSKNF(const std::string source) {
	std::string gluinres = "";
	std::vector<std::string> frags = fragmentAND2(source);

	for (int iter = 0; iter < frags.size(); iter++) {
		for (int jiter = iter + 1; jiter < frags.size(); jiter++) {
			std::string neighbs = AreNeighSKNF(frags[iter], frags[jiter]);

			if (!neighbs.empty()) {
				if (!gluinres.empty()) {
					gluinres += "*";
				}

				gluinres += neighbs;
			}
		}
	}

	return gluinres;
}

bool Excess2(const std::vector<std::string> string, int z) {
	std::vector<std::vector<std::string>> rs;
	std::vector<std::string> ds;

	for (const std::string& source : string) {
		std::vector<std::string> tem = fragmentOR(source);
		rs.push_back(tem);
	}

	std::vector<std::string> ks = rs[z];

	for (int iter = 0; iter < ks.size(); iter++) {
		for (int jiter = 0; jiter < rs.size(); jiter++) {
			if (jiter != z) {
				if (tofind(rs[jiter], revers(ks[iter]))) {
					rs.erase(rs.begin() + jiter);
				}
			}
		}
	}

	for (int iter = 0; iter < rs.size(); iter++) {
		if (iter != z) {
			for (int jiter = 0; jiter < rs[iter].size(); jiter++) {
				if (!tofind(ks, rs[iter][jiter])) {
					ds.push_back(rs[iter][jiter]);
				}
			}
		}
	}

	for (int iter = 0; iter < ds.size(); iter++) {
		if (tofind(ds, revers(ds[iter]))) {
			return true;
		}
	}

	return false;
}


std::string TKFfunc(std::string source) {
	std::vector<std::string> rel = fragmentAND2(source);
	for (int iter = 0; iter < rel.size(); iter++) {
		if (Excess2(rel, iter)) {
			source.erase(source.find(rel[iter]), rel[iter].length() + 3);
		}
	}
	return source;
}

bool Including(const std::string string1, const std::string string2) {
	std::vector<std::string> vis = fragmentAND(string1);
	for (const std::string& fragm : vis) {
		if (fragm.length() == 2) {
			if (string2.find("*" + fragm) == std::string::npos && string2.find("+" + fragm) == std::string::npos && string2.find(fragm) != 0) {
				return false;
			}
		}
		else {
			if (string2.find(fragm) == std::string::npos) {
				return false;
			}
		}
	}
	return true;
}


std::string MClassSDNF(const std::string SDNF, std::string DNF) {
	std::vector<std::string> fragSDNF = fragmentOR(SDNF);
	std::vector<std::string> fragDNF = fragmentOR(DNF);
	std::vector<std::vector<char>> tablic(fragDNF.size(), std::vector<char>(fragSDNF.size()));

	for (int iter = 0; iter < fragDNF.size(); iter++) {
		for (int jiter = 0; jiter < fragSDNF.size(); jiter++) {
			if (Including(fragDNF[iter], fragSDNF[jiter])) {
				tablic[iter][jiter] = 'X';
			}
		}
	}

	for (int iter = 0; iter < fragSDNF.size(); iter++) {
		std::cout << "\t  " << fragSDNF[iter];
	}

	for (int iter = 0; iter < fragDNF.size(); iter++) {
		std::cout << std::endl;
		std::cout << fragDNF[iter] << "     ";
		for (int jiter = 0; jiter < fragSDNF.size(); jiter++) {
			std::cout << tablic[iter][jiter] << "\t\t     ";
		}
	}

	std::vector<std::string> preRes;
	for (int iter = 0; iter < fragDNF.size(); iter++) {
		bool u = false;
		for (int jiter = 0; jiter < fragSDNF.size(); jiter++) {
			if (tablic[iter][jiter] == 'X') {
				for (int k = 0; k < fragDNF.size(); k++) {
					if (tablic[k][jiter] == 'X') {
						if (k != iter) {
							break;
						}
					}
					else if (k + 2 == fragDNF.size()) {
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
			preRes.push_back(fragDNF[iter]);
		}
	}

	for (int iter = 0; iter < preRes.size(); iter++) {
		size_t pozit = DNF.find(preRes[iter]);
		if (pozit != std::string::npos) {
			if (pozit > 0 && DNF[pozit - 1] == '!') {
				DNF.erase(pozit - 1, preRes[iter].length() + 2);
			}
			else {
				DNF.erase(pozit, preRes[iter].length() + 1);
			}
		}
	}

	return DNF;
}


bool including2(const string string1, const string string2) {
	vector<string> vis = fragmentOR(string1);
	for (const string& fragm : vis) {
		if (fragm.length() == 2) {
			if (string2.find("+" + fragm) == string::npos && string2.find(fragm) != 0)
				return false;
		}
		else {
			if (string2.find(fragm) == string::npos)
				return false;
		}
	}
	return true;
}


string MClassSKNF(const string SKNF, string KNF) {
	vector<string> hek = fragmentAND2(SKNF);
	vector<string> lek = fragmentAND2(KNF);
	vector<vector<char>> tablic(lek.size(), vector<char>(hek.size()));

	for (int iter = 0; iter < lek.size(); iter++) {
		for (int jiter = 0; jiter < hek.size(); jiter++) {
			if (including2(lek[iter], hek[jiter]))
				tablic[iter][jiter] = 'X';
		}
	}

	for (const string& fragm : hek) {
		cout << "\t  " << fragm;
	}

	for (int iter = 0; iter < lek.size(); iter++) {
		cout << '\n' << lek[iter] << "     ";
		for (int jiter = 0; jiter < hek.size(); jiter++) {
			cout << tablic[iter][jiter] << "\t\t     ";
		}
	}

	vector<string> res;
	for (int iter = 0; iter < lek.size(); iter++) {
		bool u = false;
		for (int jiter = 0; jiter < hek.size(); jiter++) {
			if (tablic[iter][jiter] == 'X') {
				for (int kiter = 0; kiter < lek.size(); kiter++) {
					if (tablic[kiter][jiter] == 'X') {
						if (kiter != iter)
							break;
					}
					else if (kiter + 2 == lek.size()) {
						u = true;
						break;
					}
				}
			}
			if (u)
				break;
		}
		if (!u)
			res.push_back(lek[iter]);
	}

	for (const string& frag : res) {
		if (!KNF.find(frag))
			KNF.erase(0, frag.length() + 1);
		else
			KNF.erase(KNF.find(frag) - 1, frag.length() + 3);
	}

	return KNF;
}


vector<vector<int>> DrawDiagr(int countOfArgs) {
	int horizO;
	vector<vector<int>> diagr;
	if (countOfArgs % 2 == 0) {
		diagr.resize(pow(2, countOfArgs / 2));
		horizO = pow(2, countOfArgs / 2);
	}
	else {
		diagr.resize(pow(2, (countOfArgs - 1) / 2));
		horizO = pow(2, (countOfArgs + 1) / 2);
	}
	for (int iter = 0; iter < diagr.size(); iter++) {
		vector<int> t(horizO);
		diagr[iter] = t;
	}
	return diagr;
}

unsigned int GrCod(unsigned int kod) {
	return kod ^ (kod >> 1);
}

string twoten(int y, int z) {
	string ken;
	int iter = 0;
	long long citer = 0;
	while (y != 0) {
		while (y - pow(2, iter + 1) >= 0) {
			iter++;
		}
		y -= pow(2, iter);
		citer += pow(10, iter);
		iter = 0;
	}
	ken = to_string(citer);
	while (ken.length() < z) {
		ken = '0' + ken;
	}
	return ken;
}

bool including3(string strin, string strss) {
	vector<string> Str = fragmentOR(strss);
	for (int iter = 0; iter < Str.size(); iter++) {
		if (Including(strin, Str[iter])) {
			return true;
		}
	}
	return false;
}


string SearchTDF(string string1, string string2) {
	string dlin = "";
	for (int iter = 0; iter < string1.length(); iter++) {
		if (string1[iter] == '0' && string2[iter] == '0')
			dlin += "*!x" + to_string(iter + 1);
		if (string1[iter] == '1' && string2[iter] == '1')
			dlin += "*x" + to_string(iter + 1);
	}
	dlin.erase(0, 1);
	return dlin;
}

vector<string> norm(vector<string> source) {
	vector<string> test;
	for (int i = 0; i < source.size(); i++) {
		if (!tofind(test, source[i]))
			test.push_back(source[i]);
	}
	for (int iter = 0; iter < test.size(); iter++) {
		vector<string> fr = fragmentAND(test[iter]);
		bool g = false;
		for (int jiter = 0; jiter < test.size() - 1; jiter++) {
			if (jiter != iter) {
				if ((Including(fr[0], test[jiter]) && Including(fr[1], test[jiter + 1])) ||
					(Including(fr[1], test[jiter]) && Including(fr[0], test[jiter + 1]))) {
					test.erase(test.begin() + iter);
					g = true;
					break;
				}
			}
		}
		if (g) {
			break;
		}
	}
	return test;
}

string Carno(string SDNF, int countOfArgs) {
	vector<vector<int>> diagr = DrawDiagr(countOfArgs);
	vector<string> ven;
	vector<string> glen;
	vector<string> ans;
	string TF;
	int horizO = (countOfArgs % 2 == 0) ? pow(2, countOfArgs / 2) : pow(2, (countOfArgs + 1) / 2);
	int vertO = pow(2, countOfArgs - log2(horizO));
	for (int iter = 0; iter < vertO; iter++)
		ven.push_back(twoten(GrCod(iter), log2(vertO)));
	for (int iter = 0; iter < horizO; iter++)
		glen.push_back(twoten(GrCod(iter), log2(horizO)));
	for (int iter = 0; iter < diagr.size(); iter++) {
		for (int jiter = 0; jiter < diagr[iter].size(); jiter++) {
			string s = ven[iter] + glen[jiter];
			string b = "";
			for (int ker = 0; ker < s.length(); ker++) {
				if (s[ker] == '0') {
					b += (b.empty()) ? "!x" + to_string(ker + 1) : "*!x" + to_string(ker + 1);
				}
				else {
					b += (b.empty()) ? "x" + to_string(ker + 1) : "*x" + to_string(ker + 1);
				}
			}
			diagr[iter][jiter] = (including3(b, SDNF)) ? 1 : 0;
		}
	}

	for (int iter = 0; iter < glen.size(); iter++) {
		cout << "\t" << glen[iter];
	}

	for (int iter = 0; iter < ven.size(); iter++) {
		cout << '\n' << ven[iter] << "      ";
		for (int jiter = 0; jiter < glen.size(); jiter++) {
			cout << diagr[iter][jiter] << "\t ";
		}
	}

	for (int iter = 0; iter < diagr.size(); iter++) {
		for (int jiter = 0; jiter < diagr[iter].size(); jiter++) {
			if (diagr[iter][jiter] == 1) {
				if (iter + 1 < diagr.size() && diagr[iter + 1][jiter] == 1)
					ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter + 1] + glen[jiter]));
				if (iter - 1 >= 0 && diagr[iter - 1][jiter] == 1)
					ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter - 1] + glen[jiter]));
				if (jiter - 1 >= 0) {
					if (diagr[iter][jiter - 1] == 1)
						ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter] + glen[jiter - 1]));
				}
				else {
					if (diagr[iter][glen.size() - 1] == 1)
						ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter] + glen[glen.size() - 1]));
				}
				if (jiter + 1 < glen.size()) {
					if (diagr[iter][jiter + 1] == 1)
						ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter] + glen[jiter + 1]));
				}
				else {
					if (diagr[iter][0] == 1)
						ans.push_back(SearchTDF(ven[iter] + glen[jiter], ven[iter] + glen[0]));
				}
			}
		}
	}
	ans = norm(ans);

	for (int iter = 0; iter < diagr.size(); iter++) {
		TF += "+" + ans[iter];
	}

	TF.erase(0, 1);
	return TF;
}


bool including4(string strin, string strss) {
	vector<string> frags = fragmentAND2(strss);
	for (int iter = 0; iter < frags.size(); iter++) {
		if (including2(strin, frags[iter])) {
			return true;
		}
	}
	return false;
}

string SearchTKF(string string1, string string2) {
	string res = "(";
	for (int iter = 0; iter < string1.length(); iter++) {
		if (string1[iter] == '0' && string2[iter] == '0') {
			res += "+x" + to_string(iter + 1);
		}
		else if (string1[iter] == '1' && string2[iter] == '1') {
			res += "+!x" + to_string(iter + 1);
		}
	}
	res.erase(1, 1);
	res += ")";
	return res;
}


vector<string> norm2(vector<string> sorce) {
	vector<string> tem;
	for (int iter = 0; iter < sorce.size(); iter++) {
		string substring = sorce[iter].substr(1, sorce[iter].length() - 2);
		if (!tofind(tem, substring)) {
			tem.push_back(substring);
		}
	}

	for (int jiter = 0; jiter < tem.size(); jiter++) {
		vector<string> frags = fragmentOR(tem[jiter]);
		bool searchedSovpadenie = false;
		int searchCount = 0;
		for (int iter = 0; iter < tem.size(); iter++) {
			if (iter != jiter) {
				if (including2(frags[searchCount], tem[iter])) {
					searchCount++;
				}
			}
			if (searchCount == 2) {
				tem.erase(tem.begin() + jiter);
				searchedSovpadenie = true;
				break;
			}
		}
		if (searchedSovpadenie) {
			break;
		}
	}

	return tem;
}

string CarnoTwo(string SKNF, int nn) {
	vector<vector<int>> diagr = DrawDiagr(nn);
	vector<string> viw;
	vector<string> z;
	vector<string> ans;
	string TF;
	int horizlO;
	int vertO;
	if (nn % 2 == 0) {
		horizlO = pow(2, nn / 2);
		vertO = pow(2, nn / 2);
	}
	else {
		horizlO = pow(2, (nn + 1) / 2);
		vertO = pow(2, (nn - 1) / 2);
	}
	for (int iter = 0; iter < vertO; iter++)
		viw.push_back(twoten(GrCod(iter), log2(vertO)));
	for (int iter = 0; iter < horizlO; iter++)
		z.push_back(twoten(GrCod(iter), log2(horizlO)));
	for (int iter = 0; iter < diagr.size(); iter++)
	{
		for (int jiter = 0; jiter < diagr[iter].size(); jiter++)
		{
			string sec = viw[iter] + z[jiter];
			string bil = "";
			for (int k = 0; k < sec.length(); k++)
			{

				if (sec[k] == '0')
				{
					if (bil == "")
					{
						bil += "x" + to_string(k + 1);
					}
					else
					{
						bil += "+x" + to_string(k + 1);
					}
				}
				else
				{
					if (bil == "")
					{
						bil += "!x" + to_string(k + 1);
					}
					else
					{
						bil += "+!x" + to_string(k + 1);
					}
				}
			}
			if (!including4(bil, SKNF))
				diagr[iter][jiter] = 0;
			else
				diagr[iter][jiter] = 1;
		}
	}
	for (int iter = 0; iter < z.size(); iter++)
		cout << "\t" << z[iter];
	for (int iter = 0; iter < viw.size(); iter++)
	{
		cout << '\n' << viw[iter] << "      ";
		for (int jiter = 0; jiter < z.size(); jiter++)
			cout << diagr[iter][jiter] << "\t ";
	}
	for (int iter = 0; iter < diagr.size(); iter++)
	{
		for (int jiter = 0; jiter < diagr[iter].size(); jiter++)
		{
			if (!diagr[iter][jiter])
			{
				if (iter + 1 < diagr.size())
					if (!diagr[iter + 1][jiter])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter + 1] + z[jiter]));
				if (iter - 1 >= 0)
					if (!diagr[iter - 1][jiter])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter - 1] + z[jiter]));
				if (jiter - 1 >= 0)
				{
					if (!diagr[iter][jiter - 1])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter] + z[jiter - 1]));
				}
				else
				{
					if (!diagr[iter][z.size() - 1])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter] + z[z.size() - 1]));
				}
				if (jiter + 1 < z.size())
				{
					if (!diagr[iter][jiter + 1])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter] + z[jiter + 1]));
				}
				else
				{
					if (!diagr[iter][0])
						ans.push_back(SearchTKF(viw[iter] + z[jiter], viw[iter] + z[0]));
				}

			}
		}
	}
	ans = norm2(ans);
	for (int iter = 0; iter < diagr.size(); iter++)
	{
		TF += ")*(" + ans[iter];
	}
	TF.erase(0, 2);
	TF += ')';
	return TF;
}