#include "HashTable.h"

template<typename Key, typename Value>
int HashTable<Key, Value>::hash(const string& key) const
{
	return (key[0] * 26 + key[1]) % 100;
}

template<typename Key, typename Value>
int HashTable<Key, Value>::hash(const Key& key) const
{
	return key % this->size;
}

template<typename Key, typename Value>
HashTable<Key, Value>::HashTable()
{
	for (int i = 0; i < this->size; ++i) {
		table[i] = nullptr;
	}
}

template<typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
}

template<typename Key, typename Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value)
{
	if (table[hash(key)] == nullptr) {
		this->table[hash(key)] = new Node(key, value);
	}
	else {
		int  i = hash(key);
		while (table[i] != nullptr) {
			if (table[i]->key == key) {
				throw exception("This key is already exists");
			}
			++i;
		}
		table[i] = new Node(key, value);
	}
}

template<typename Key, typename Value>
void HashTable<Key, Value>::erase(const Key& key)
{
	Node* search = table[hash(key)];
	if (search == nullptr) {
		throw exception("This key doesn't exist in table");
	}
	int i = hash(key);
	while (table[i + 1] != nullptr && table[i + 1]->key != key) {
		++i;
	}
	if (table[i + 1]) {
		table[i + 1] = nullptr;
	}
	else {
		throw exception("There is no data with such key");
	}
}

template<typename Key, typename Value>
void HashTable<Key, Value>::clear()
{
	for (int i = 0; i < this->size; ++i) {
		this->table[i] = nullptr;
	}
}

template<typename Key, typename Value>
bool HashTable<Key, Value>::empty() const
{
	for (int i = 0; i < this->size; ++i) {
		if (table[i] != nullptr)
			return false;
	}

	return true;
}

template<typename Key, typename Value>
int HashTable<Key, Value>::maxSize() const
{
	return this->size;
}

template<typename Key, typename Value>
Value& HashTable<Key, Value>::operator[](const Key& key) const
{
	int  i = hash(key);
	while (table[i] != nullptr && table[i]->key != key)
	{
		++i;
	}
	if (table[i] != nullptr) {
		return table[i]->value;
	}
	else {
		throw exception("There is no data with such key");
	}
}
