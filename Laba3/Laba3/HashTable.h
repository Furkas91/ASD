#pragma once
#include <set>
#include <iostream>

using std::set;

struct list
{
	list* next;
	int value;

	list()
	{
		next = nullptr;
		value = 0;
	}

	list(list& L)
	{
		value = L.value;
		if (L.next != nullptr)
			next = new list(*L.next);
		else
			next = nullptr;
	}

	~list()
	{
		if (next != nullptr)
		{
			delete next;
			next = nullptr;
		}
	}
};

class HashTable
{
private:
	set<int> keys;
	list* values[1000]; // Ìàññèâ óêàçàòåëåé íà 1000 ýëåìåíòîâ. Ïðîñòî ïîòîìó ÷òî ìíå ëåíü
	int size;

	int hashfunc(int key) const
	{
		return (a * key + b) % size;
	}

	void clear(int s)
	{
		size = s;
		keys.clear();

		for (int i = 0; i < 1000; ++i)
			if (values[i] != nullptr)
			{
				delete values[i];
				values[i] = nullptr;
			}
	}

	void clear()
	{
		clear(0);
	}

public:
	static int a, b; // Ïðîñòûå ÷èñëà äëÿ ãåíåðàöèè õýøà. A áëèçêî ê size, B áëèçêî ê 1
	HashTable(int size) : size(size) {}

	HashTable(const HashTable& H)
	{
		size = H.size;
		keys = H.keys;

		for (int i = 0; i < 1000; ++i)
			if (H.values[i] != nullptr)
				values[i] = new list(*H.values[i]);
			else
				values[i] = nullptr;
	}

	HashTable(HashTable&& H)
	{
		size = H.size;
		keys = H.keys;

		for (int i = 0; i < 1000; ++i)
		{
			values[i] = H.values[i];
			H.values[i] = nullptr;
		}
	}

	~HashTable()
	{
		clear();
	}

	HashTable& operator=(const HashTable& H)
	{
		if (this != &H)
		{
			clear(H.size);

			size = H.size;
			keys = H.keys;

			for (int i = 0; i < 1000; ++i)
				if (H.values[i] != nullptr)
					values[i] = new list(*H.values[i]);
				else
					values[i] = nullptr;
		}

		return *this;
	}

	HashTable& operator=(HashTable&& H)
	{
		if (this != &H)
		{
			clear(H.size);

			size = H.size;
			keys = H.keys;

			for (int i = 0; i < 1000; ++i)
			{
				values[i] = H.values[i];
				H.values[i] = nullptr;
			}
		}

		return *this;
	}

	int operator[](const int& key) const
	{
		list* head = values[hashfunc(key)];
		if (head == nullptr) return -1;
		if (head->next == nullptr)
			return head->value;
		else
		{
			list* temp = head;
			// Ïîèñê íóæíîãî ýëåìåíòà
			while (temp != nullptr)
			{
				if (temp->value == key)
					return temp->value;
				temp = temp->next;
			}
		}
		return -1;
	}

	HashTable operator&(const HashTable& B)
	{
		HashTable C(*this);
		return C &= B;
	}

	HashTable& operator&=(const HashTable& B)
	{
		HashTable C(*this);
		clear(C.size < B.size ? C.size : B.size);
		// Ìàêñèìàëüíûé ðàçìåð êîíúþíêöèè - ðàçìåð ìåíüøåãî ìíîæåñòâà

		set<int> keysC = C.keys;

		for (auto i : keysC)
		{
			// Åñëè B[i] âåðíåò i, çíà÷èò â îáîèõ ìíîæåñòâàõ åñòü ýëåìåíò - äîáàâëÿåì â êîíúþíêöèþ
			if (B[i] == i)
				add(i);
		}

		return *this;
	}

	HashTable operator|(const HashTable& B)
	{
		HashTable C(*this);
		return C |= B;
	}

	HashTable& operator|=(const HashTable& B)
	{
		HashTable C(*this);
		clear(C.size + B.size);
		// Ìàêñèìàëüíûé ðàçìåð äèçúþíêöèè - ñóììà ðàçìåðîâ

		set<int> keysC = C.keys;

		for (auto i : keysC)
			add(i);

		set<int> keysB = B.keys;

		for (auto i : keysB)
			add(i);

		return *this;
	}

	HashTable operator-(const HashTable& B)
	{
		HashTable C(*this);
		return C -= B;
	}

	HashTable& operator-=(const HashTable& B)
	{
		HashTable C(*this);
		clear(C.size);
		// Ìàêñèìàëüíûé ðàçìåð âû÷èòàíèÿ - ðàçìåð ïåðâîãî îïåðàíäà

		set<int> keysC = C.keys;

		for (auto i : keysC)
		{
			// Åñëè B[i] âåðíåò i, çíà÷èò â îáîèõ ìíîæåñòâàõ åñòü ýëåìåíò - ÍÅ äîáàâëÿåì â ðàçíîñòü
			if (!(B[i] == i))
				add(i);
		}

		return *this;
	}

	HashTable operator+(const HashTable& B)
	{
		HashTable C(*this);
		return C += B;
	}

	HashTable& operator+=(const HashTable& B)
	{
		HashTable C(*this);
		clear();

		*this = (C | B) - (C & B);

		return *this;
	}

	void add(int keyAndValue)
	{
		add(keyAndValue, keyAndValue);
	}

	void add(int key, int value)
	{
		keys.insert(key);

		list* head = values[hashfunc(key)];
		if (head == nullptr)
		{
			head = new list;
			head->next = nullptr;
			head->value = value;
			values[hashfunc(key)] = head;
		}
		else
		{
			// Ìîæåò òàêîå çíà÷åíèå óæå åñòü?
			list* t = head;
			bool f = false;
			while (!f && t != nullptr)
			{
				f = value == t->value;
				t = t->next;
			}

			if (!f)
			{
				// t - ýëåìåíò ïîñëå êîòîðîãî áóäåò íîâàÿ âñòàâêà
				list* t = head;
				while (t->next != nullptr)
					t = t->next;

				list* insert = new list;
				insert->next = nullptr;
				insert->value = value;
				t->next = insert;
			}
		}
	}

	set<int> getKeys()
	{
		return keys;
	}

	bool valueExists(int key)
	{
		list* head = values[hashfunc(key)];
		list* t = head;
		bool f = false;
		while (!f && t != nullptr)
		{
			f = key == t->value;
			t = t->next;
		}

		return f;
	}

	int getSize()
	{
		return size;
	}
};