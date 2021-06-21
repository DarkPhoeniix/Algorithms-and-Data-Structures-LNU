#pragma once

using namespace std;

template <typename Value>
class Queue
{
public:
	Queue();
	~Queue();
	void push_back(const Value& value);
	void pop_front();
	Value& front() const;
	Value& end() const;
	int size() const;
	bool empty() const;

private:
	class Node {
	public:
		Value value;
		Node* next;
		Node* prev;
		Node(const Value& value);
	};

	Node* head;
	Node* tail;
	int sz;
};
