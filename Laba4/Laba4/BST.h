#pragma once
#include <iostream>

struct Node
{
	Node *left, *right;
	unsigned char height;
	int value;

	Node() : value(0), left(nullptr), right(nullptr), height(0) {}
	Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
};

class Bst
{
private:
	enum DisplayDirection
	{
		forward,
		backward
	};


	void inWidthDisplay(Node *root, DisplayDirection dir)
	{
		if (dir == forward)
			if (root != nullptr)
			{
				inWidthDisplay(root->left, forward);
				std::cout << root->value << "; ";
				inWidthDisplay(root->right, forward);
			}
		if (dir == backward)
			if (root != nullptr)
			{
				inWidthDisplay(root->right, backward);
				std::cout << root->value << "; ";
				inWidthDisplay(root->left, backward);
			}
	}


public:
	Node* root;
	Bst() {}
	Bst(int* data, int arraylength)
	{
		root = nullptr;
		build(data, arraylength);
	}

	void build(int* data, int arraylength) //Ñáîðêà ÄÄÏ èç ìàññèâà óçëîâ data
	{
		for (int i = 0; i < arraylength; ++i)
			root = insert(root, data[i]);
	}

	unsigned char height(Node* p)
	{
		return p ? p->height : 0;
	}

	int bfactor(Node* p)
	{
		return height(p->right) - height(p->left);
	}

	void fixheight(Node* p)
	{
		unsigned char hl = height(p->left);
		unsigned char hr = height(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}

	Node* rotateright(Node* p) // ïðàâûé ïîâîðîò âîêðóã p
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		fixheight(p);
		fixheight(q);
		return q;
	}

	Node* rotateleft(Node* q) // ëåâûé ïîâîðîò âîêðóã q
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		fixheight(q);
		fixheight(p);
		return p;
	}

	Node* balance(Node* p) // áàëàíñèðîâêà óçëà p
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p; // áàëàíñèðîâêà íå íóæíà
	}

	Node* insert(Node* p, int k) // âñòàâêà êëþ÷à k â äåðåâî ñ êîðíåì p
	{
		if (!p) return new Node(k);
		if (k < p->value)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);
		return balance(p);
		//return p;
	}

	void print_Tree(Node * p, int level)
	{
		if (p)
		{
			print_Tree(p->right, level + 1);
			for (int i = 0; i < level; i++) std::cout << "   ";
			std::cout << p->value << std::endl;
			print_Tree(p->left, level + 1);
		}
	}

	bool operator[] (int value)
	{
		return search(this->root, value);
	}

	bool search(Node* n, int value)
	{
		if (n == nullptr) return false;

		if (n->value == value) return true;

		if (n->value < value)
			return search(n->right, value);
		else
			return search(n->left, value);
	}

	void displayForward()
	{
		inWidthDisplay(root, forward);
	}

	void displayBackward()
	{
		inWidthDisplay(root, backward);
	}
};