#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

vector<string> fragmentAND(string);

vector<string> fragmentAND2(string);

string AreNeighSDNF(string, string);

vector<string> fragmentOR(string);

string gluiSDNF(string);

string revers(string);

bool tofind(vector<string>, string);

bool Excess(vector<string>, int);

string TDFfunc(string);

string AreNeighSKNF(string, string);

string gluiSKNF(string);

bool Excess2(vector<string>, int);

string TKFfunc(string);

bool Including(string, string);

string MClassSDNF(string, string);

bool including2(string, string);

string MClassSKNF(string, string);

vector<vector<int>> DrawDiagr(int);

unsigned int GrCod(unsigned int);

string twoten(int, int);

bool including3(string, string);

string SearchTDF(string, string);

vector<string> norm(vector<string>);

string Carno(string, int);

bool including4(string, string);

string SearchTKF(string, string);

vector<string> norm2(vector<string>);

string CarnoTwo(string, int);

#endif