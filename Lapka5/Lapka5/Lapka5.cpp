#include "pch.h"
#include <iostream>
#include "HashTable.h"
#include <ctime>
#include <windows.h>

using std::cin;
using std::cout;
using std::endl;

void DisplayHashTable(HashTable& table)
{
	for (int i = 0; i < table.size(); ++i)
	{
		cout.width(3);
		cout << table[i];
	}
	cout << endl;
}

int main()
{

	std::srand(unsigned(std::time(0)));

	HashTable setA(10, 25);
	cout << "A:";
	DisplayHashTable(setA);

	HashTable setB(10, 25);
	cout << "B:";
	DisplayHashTable(setB);

	HashTable setC(10, 25);
	cout << "C:";
	DisplayHashTable(setC);

	HashTable setD(0, 0); //this is for merge


	cout << endl;

	//setA.subst(setB,3);
	//DisplayHashTable(setA);

	setD.merge(setA, setB);
	DisplayHashTable(setD);

	//setA.concat(setB);
	//cout << "1:";
	//DisplayHashTable(setA);
	//setA.mul(1);
	//cout << "2:";
	//DisplayHashTable(setA);
	//setA.concat(setC);
	//cout << "3:";
	//DisplayHashTable(setA);
	//setA.excl(setB);
	//cout << "4:";
	//DisplayHashTable(setA);

	system("pause");

	return 0;
}
