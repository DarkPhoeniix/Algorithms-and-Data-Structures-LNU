#pragma once

using namespace std;

template <typename Value>
class PriorityQueue
{
public:
	PriorityQueue();
	~PriorityQueue();
	void push_back(const Value& value, const int& priority);
	void pop_front();
	Value& front();
	Value& end();
	int size() const;
	bool empty() const;

private:
	class Node {
	public:
		Value value;
		Node* next;
		Node* prev;
		int priority;
		Node(const Value& value, const int& priority);
	};
	Node* head;
	Node* tail;
	int sz;
};




