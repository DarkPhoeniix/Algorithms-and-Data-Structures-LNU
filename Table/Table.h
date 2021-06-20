#pragma once
#include <iostream>

using namespace std;

template<typename Key, typename Value>
class Table
{
public:
	Table();
	~Table();

	void insert(const Key& key, const Value& value);
	void erase(const Key& key);
	bool find(const Key& key) const;
	void clear();
	bool empty() const;
	int size() const;

	Value& operator[](const Key& key);

private:
	class Node
	{
	public:
		Node()
		{	}
		Node(const Key& key, const Value& value)
			: key(key), value(value), nextLeft(nullptr), nextRight(nullptr)
		{	}
		~Node()
		{	
			delete nextLeft;
			delete nextRight;
		}

		Node* nextLeft;
		Node* nextRight;
		Key key;
		Value value;
	};

	int sz;
	Node* root;
};





