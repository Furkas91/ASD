#include "pch.h"
#include "Bst.h"
#include "Generator.h"
#include "LogicalOperation.h"
#include <iostream>
#include <ctime>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;

int main()
{	/*
	Bst A = generator::GenerateSet(100, 100);
	cout << "Root is " << A.root->value << endl << endl << endl;
	A.print_Tree(A.root, 0);
	*/
	std::srand(unsigned(std::time(0)));

	Bst A, B, C, D, E, R, R1, R2, R3;

	A = generator::GenerateSet(10, 32);
	B = generator::GenerateSet(10, 32);
	C = generator::GenerateSet(10, 32);
	D = generator::GenerateSet(10, 32);
	E = generator::GenerateSet(10, 32);

	cout << "A: ";
	A.displayForward();
	cout << endl;
	cout << "B: ";
	B.displayForward();
	cout << endl;
	cout << "C: ";
	C.displayForward();
	cout << endl;
	cout << "D: ";
	D.displayForward();
	cout << endl;
	cout << "E: ";
	E.displayForward();
	cout << endl;
	cout << endl;

	// (A \ B \ C) + D v E
	//    1   2    3   4

	//(A & B) + (C | D \ E)
	//   1    4    3   2

	R1 = A & B;
	cout << "A & B: ";
	R1.displayForward();
	cout << endl;
	R2 = D - E;
	cout << "D \\ E: ";
	R2.displayForward();
	cout << endl;
	R2 = R2 | C;
	cout << "(C | D \\ E): ";
	R2.displayForward();
	cout << endl;		
	cout << endl;
	R = R1 + R2;
	cout << "(A & B) + (C | D \ E): ";
	R.displayForward();



	//R = A - B;
	//cout << "A \\ B: ";
	//R.displayForward();
	//cout << endl;
	//R = R - C;
	//cout << "A \\ B \\ C: ";
	//R.displayForward();
	//cout << endl;
	//R = R ^ D;
	//cout << "(A \\ B \\ C) + D: ";
	//R.displayForward();
	//cout << endl;
	//cout << endl;
	//R = R | E;
	//cout << "(A \\ B \\ C) + D v E: ";
	//R.displayForward();
	cout << endl;

	system("pause");

	return 0;
}