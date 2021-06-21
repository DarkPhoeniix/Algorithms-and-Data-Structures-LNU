#include "Queue.h"

template<typename Value>
Queue<Value>::Node::Node(const Value& value)
	: value(value), next(nullptr), prev(nullptr)
{	}



template<typename Value>
Queue<Value>::Queue()
	: head(nullptr), tail(nullptr), sz(0)
{	}

template<typename Value>
Queue<Value>::~Queue() {
	while (head != nullptr) {
		this->pop_front();
	}
}

template<typename Value>
void Queue<Value>::push_back(const Value& value) {
	if (head != nullptr) {
		Node* node = new Node(value);
		tail->next = node;
		node->prev = tail;
		tail = node;
	} else {
		head = tail = new Node(value);
	}
	sz++;
}

template<typename Value>
void Queue<Value>::pop_front() {
	if (head != nullptr) {
		Node* node = head;
		head = head->next;
		delete node;
		sz--;
	} else {
		throw exception("Nothing to delete");
	}
}

template<typename Value>
Value& Queue<Value>::front() const {
	if (head != nullptr) {
		return head->value;
	}
	throw exception("Queue is empty");
}

template<typename Value>
Value& Queue<Value>::end() const {
	if (tail != nullptr) {
		return tail->value;
	}
	throw exception("Queue is empty");
}

template<typename Value>
int Queue<Value>::size() const {
	return sz;
}

template<typename Value>
bool Queue<Value>::empty() const {
	if (head == nullptr) {
		return true;
	}
	return false;
}

