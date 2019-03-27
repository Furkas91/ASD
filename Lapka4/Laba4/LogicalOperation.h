#pragma once
enum inWidthTask
{
	conj,
	disj,
	sub,
	copy
};


class LogicalOperation
{
public:
	// Îáõîä äåðåâà À â øèðèíó, ñ âûïîëíåíèåì ñîîòâåòñâóþùåé îáðàáîòêè
	static void inWidth(Node* a, Bst* b, Bst* c, inWidthTask task)
	{
		if (a != nullptr)
		{
			inWidth(a->left, b, c, task);

			switch (task)
			{
			case conj:
				if ((*b)[a->value])
					c->root = c->insert(c->root, a->value);
				break;
			case disj:
			case sub:
				if (!(*b)[a->value])
					c->root = c->insert(c->root, a->value);
				break;
			case copy:
				c->root = c->insert(c->root, a->value);
			default:
				break;
			}

			inWidth(a->right, b, c, task);
		}
	}
};

Bst operator&(Bst a, Bst b)
{
	Bst* c = new Bst();
	LogicalOperation::inWidth(a.root, &b, c, conj);
	return *c;
}

Bst operator|(Bst a, Bst b)
{
	Bst* c = new Bst();
	LogicalOperation::inWidth(b.root, nullptr, c, copy); // Êîïèðîâàòü b â c
	LogicalOperation::inWidth(a.root, &b, c, disj);
	return *c;
}

Bst operator-(Bst a, Bst b)
{
	Bst* c = new Bst();
	LogicalOperation::inWidth(a.root, &b, c, sub);
	return *c;
}

Bst operator+(Bst a, Bst b)
{
	return (a | b) - (a & b);
}