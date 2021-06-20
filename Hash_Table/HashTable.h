#pragma once
#include <iostream>

using namespace std;

template<typename Key, typename Value>
class HashTable
{
private:
	int hash(const string& key) const;
	int hash(const Key& key) const;

	class Node
	{
	public:
		Key key;
		Value value;
		Node(const Key& key, const Value& value)
			: key(key), value(value)
		{	}
	};
	static const int size = 100;
	Node* table[size];

public:
	HashTable();
	~HashTable();

	void insert(const Key& key, const Value& value);
	void erase(const Key& key);
	void clear();
	bool empty() const;
	int maxSize() const;
	Value& operator[](const Key& key) const;
};
