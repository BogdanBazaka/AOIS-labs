#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include "header.h"

using namespace std;

int main()
{
	string SDNF = "x1*!x2*!x3+!x1*!x2*!x3+!x1*x2*!x3+!x1*x2*x3";
	string SKNF = "(!x1+!x2+!x3)*(x1+x2+!x3)*(!x1+x2+!x3)*(!x1+!x2+x3)";

	string DNF = gluiSDNF(SDNF);
	cout << "\nDNF: " << DNF << "\n\nTDF: ";
	string TDF = TDFfunc(DNF);
	cout << TDF << "\n\nKNF: ";

	string KNF = gluiSKNF(SKNF);
	cout << KNF << "\n\nTKF: ";
	string TKF = TKFfunc(KNF);
	cout << TKF << "\n\n";

	for (int iter = 0; iter < 80; cout << '.', iter++);
	cout << "\n\n";

	TDF = MClassSDNF(SDNF, DNF);
	cout << "\n\n" << TDF << "\n\n";
	TKF = MClassSKNF(SKNF, KNF);
	cout << "\n\n" << TKF << "\n\n";

	for (int i = 0; i < 80; cout << '.', i++);
	cout << "\n\n";

	TDF = Carno(SDNF, 3);
	cout << "\n\n" << TDF << "\n\n";
	TKF = CarnoTwo(SKNF, 3);
	cout << "\n\n" << TKF << '\n';

	system("pause > NUL");
	return 0;
}