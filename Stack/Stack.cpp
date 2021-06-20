#include "Stack.h"

Stack::Stack()
	: arr(nullptr), size(0)
{	}

Stack::Stack(const int& value)
	: arr(new int[size] {value}), size(1)
{	}

Stack::~Stack()
{
	delete[] arr;
}



void Stack::push(const int& value)
{
	int* newArr = new int[++this->size];

	for (int i = 0; i < this->size - 1; ++i) {
		newArr[i] = arr[i];
	}
	newArr[this->size - 1] = value;
	delete[] arr;
	this->arr = newArr;
}

void Stack::pop()
{
	int* newArr = new int[--this->size];

	for (int i = 0; i < this->size; ++i) {
		newArr[i] = arr[i];
	}
	delete[] this->arr;
	this->arr = newArr;
}



int Stack::top() const
{
	return this->arr[this->size - 1];
}

int Stack::getSize() const
{
	return this->size;
}

bool Stack::empty() const
{
	if (this->arr == nullptr) {
		return true;
	}
	return false;
}
