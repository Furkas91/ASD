#pragma once
#include "HashTable.h"

class generator
{
public:
	static HashTable GenerateSet(int size, int maxValue)
	{
		HashTable table(size);

		maxValue++;
		while (table.getKeys().size() < size)
			table.add(rand() % maxValue);

		return table;
	}
};