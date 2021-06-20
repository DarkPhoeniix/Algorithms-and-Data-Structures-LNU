#pragma once

class Stack
{
public:
	Stack();
	Stack(const int& value);
	~Stack();
	void push(const int& value);
	void pop();
	int top() const;
	int getSize() const;
	bool empty() const;
	
private:
	int size;
	int* arr;
};

