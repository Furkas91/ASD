#pragma once
#include "Bst.h"
#include <cstdlib>
#include <iostream>

class generator
{
public:
	static Bst GenerateSet(int size, int maxValue)
	{
		++maxValue;
		int* raw = new int[size];

		for (int i = 0; i < size; ++i)
		{
			do
			{
				raw[i] = std::rand() % maxValue;
			} while (repeatExists(raw, i, raw[i]));
		}

		// Maybe (size - 1)
		return Bst(raw, size);
	}

private:
	static bool repeatExists(int* arr, int size, int value)
	{
		for (int i = 0; i < size; ++i)
		{
			if (arr[i] == value) return true;
		}
		return false;
	}
};