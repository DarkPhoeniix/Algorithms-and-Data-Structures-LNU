#include "PriorityQueue.h"

template<typename Value>
PriorityQueue<Value>::Node::Node(const Value& value, const int& priority)
	: value(value), next(nullptr), prev(nullptr), priority(priority)
{	}



template<typename Value>
PriorityQueue<Value>::PriorityQueue()
	: head(nullptr), tail(nullptr), sz(0)
{	}

template<typename Value>
PriorityQueue<Value>::~PriorityQueue() {
	while (head != nullptr)
		this->pop_front();
}

template<typename Value>
void PriorityQueue<Value>::push_back(const Value& value, const int& priority) {
	if (head != nullptr) {
		Node* node = new Node(value, priority);
		Node* search = head;
		while (search != nullptr && search->priority < node->priority)
			search = search->next;
		if (search != nullptr) {
			node->next = search;
			if (search->prev != nullptr) {
				node->prev = search->prev;
				search->prev->next = node;
			}
			else
				head = node;
		}
		else {
			tail->next = node;
			node->prev = tail;
			tail = node;
		}
	}
	else
		head = tail = new Node(value, priority);
	sz++;
}

template<typename Value>
void PriorityQueue<Value>::pop_front() {
	if (head == nullptr)
		throw exception("Nothing to delete");
	else {
		Node* node = head;
		head = head->next;
		delete node;
		sz--;
	}
}

template<typename Value>
Value& PriorityQueue<Value>::front() {
	if (head == nullptr) {
		throw exception("Queue is empty");
	} else {
		return head->value;
	}
}

template<typename Value>
Value& PriorityQueue<Value>::end() {
	if (tail == nullptr) {
		throw exception("Queue is empty");
	} else {
		return tail->value;
	}
}

template<typename Value>
int PriorityQueue<Value>::size() const {
	return sz;
}

template<typename Value>
bool PriorityQueue<Value>::empty() const {
	if (head == nullptr)
		return true;
	return false;
}
