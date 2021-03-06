#include "pch.h"
#include "HashTable.h"
#include "Generator.h"
#include <iostream>
#include <ctime>
#include <windows.h>

int HashTable::a = 23;
int HashTable::b = 3;

using std::cin;
using std::cout;
using std::endl;

void DisplayHashTable(HashTable& table)
{
	set<int> s = table.getKeys();

	for (auto i : s)
		if (table[i] != -1)
		{
			cout.width(3);
			cout << i;
		}
	cout << endl;
}

int main()
{

	std::srand(unsigned(std::time(0)));
	/*
	HashTable D(26);
	for (int i = 0; i < 26; ++i)
	{
		int t;
		cin >> t;
		D.add(t);
		system("cls");
		DisplayHashTable(D);
	}*/

	HashTable setA = generator::GenerateSet(25, 31);
	cout << "A:";
	DisplayHashTable(setA);

	HashTable setB = generator::GenerateSet(25, 31);
	cout << "B:";
	DisplayHashTable(setB);

	HashTable setC = generator::GenerateSet(25, 31);
	cout << "C:";
	DisplayHashTable(setC);

	HashTable setD = generator::GenerateSet(25, 31);
	cout << "D:";
	DisplayHashTable(setD);

	HashTable setE = generator::GenerateSet(25, 31);
	cout << "E:";
	DisplayHashTable(setE);

	// Çàäàíèå:
	// (A \ B \ C) + D v E
	//    1   2    3   4


	// (A & B) + (C | D \ E)
	//    1    4    3   2 

	cout << endl;

	HashTable set1 = setA & setB;
	cout << "       A & B:       ";
	DisplayHashTable(set1);

	HashTable set2 = setD - setE;
	cout << "     D \\ E:     ";
	DisplayHashTable(set2);

	HashTable set3 = set2 | setC;
	cout << "  (C | D \\ E):  ";
	DisplayHashTable(set3);

	HashTable set4 = set3 + set1;
	cout << "(A & B) + (C | D \\ E):";
	DisplayHashTable(set4);


	//HashTable set1 = setA - setB;
	//cout << "       A \\ B:       ";
	//DisplayHashTable(set1);

	//HashTable set2 = set1 - setC;
	//cout << "     A \\ B \\ C:     ";
	//DisplayHashTable(set2);

	//HashTable set3 = set2 + setD;
	//cout << "  (A \\ B \\ C) + D:  ";
	//DisplayHashTable(set3);

	//HashTable set4 = set3 | setE;
	//cout << "(A \\ B \\ C) + D v E:";
	//DisplayHashTable(set4);

	system("pause");

	return 0;
}