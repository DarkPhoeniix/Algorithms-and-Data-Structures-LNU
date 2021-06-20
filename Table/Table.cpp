#include "Table.h"

template<typename Key, typename Value>
Table<Key, Value>::Table()
	: root(nullptr), sz(0)
{	}

template<typename Key, typename Value>
Table<Key, Value>::~Table()
{
	this->clear();
	delete root;
}



template<typename Key, typename Value>
void Table<Key, Value>::insert(const Key& key, const Value& value)
{
	++sz;
	if (this->root == nullptr) {
		this->root = new Node(key, value);
		return;
	}

	Node* search = this->root;

	while (search != nullptr) {
		if (key < search->key) {
			if (search->nextLeft != nullptr) {
				search = search->nextLeft;
			}
			else {
				search->nextLeft = new Node(key, value);
				return;
			}
		}
		else if (key > search->key) {
			if (search->nextRight != nullptr) {
				search = search->nextRight;
			}
			else {
				search->nextRight = new Node(key, value);
				return;
			}
		}
	}
}

template<typename Key, typename Value>
void Table<Key, Value>::erase(const Key& key)
{
	--sz;
	Node* search = this->root;

	while (search != nullptr && search->key != key) {
		if (key < search->key) {
			search = search->nextLeft;
		}
		else if (key > search->key) {
			search = search->nextRight;
		}
	}

	if (search == nullptr) {
		throw exception("The key doesn't exist");
	}
	else if (search->nextLeft == NULL && search->nextRight == NULL) {
		if (search == root) {
			root = nullptr;
		}
		search->key = NULL;
		search->nextLeft = nullptr;
		search->nextRight = nullptr;
		search = nullptr;
	}
	else if (search->nextLeft == nullptr) {
		Node* temp = search->nextRight;
		search->nextRight = nullptr;
		search->key = temp->key;
		search->value = temp->value;
		search->nextLeft = temp->nextLeft;
		search->nextRight = temp->nextRight;
	}
	else if (search->nextRight == nullptr) {
		Node* temp = search->nextLeft;
		search->nextLeft = nullptr;
		search->key = temp->key;
		search->value = temp->value;
		search->nextLeft = temp->nextLeft;
		search->nextRight = temp->nextRight;
	}
	else {
		Node* temp = search->nextRight;
		while (temp->nextLeft != nullptr) {
			temp = temp->nextLeft;
		}
		search->value = temp->value;
		search->key = temp->key;
		search->nextLeft = temp->nextLeft;
		search->nextRight = temp->nextRight;
	}
}

template<typename Key, typename Value>
bool Table<Key, Value>::find(const Key& key) const
{
	if (this->root == nullptr) {
		return false;
	}
	Node* search = this->root;

	while (search != nullptr && search->key != key) {
		if (key < search->key) {
			search = search->nextLeft;
		}
		else if (key > search->key) {
			search = search->nextRight;
		}
	}

	if (search) {
		return true;
	}
	return false;
}

template<typename Key, typename Value>
void Table<Key, Value>::clear()
{
	sz = 0;
	while (this->root != NULL) {
		erase(this->root->key);
	}
}

template<typename Key, typename Value>
bool Table<Key, Value>::empty() const
{
	if (this->root != nullptr) {
		return false;
	}
	return true;
}

template<typename Key, typename Value>
int Table<Key, Value>::size() const
{
	return this->sz;
}

template<typename Key, typename Value>
Value& Table<Key, Value>::operator[](const Key& key)
{
	if (this->root == nullptr) {
		throw exception("Table is empty");
	}
	Node* search = this->root;

	while (search != NULL && search->key != key) {
		if (key < search->key) {
			search = search->nextLeft;
		}
		else if (key > search->key) {
			search = search->nextRight;
		}
	}

	if (search) {
		return search->value;
	}

	throw exception("Wrong key");
}

