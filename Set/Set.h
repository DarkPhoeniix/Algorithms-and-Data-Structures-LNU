#pragma once
#include <iostream>

class Set
{
public:
	Set();
	Set(const Set& copy);

	void add(const char& elem);
	void remove(const char& elem);
	bool isInSet(const char& elem) const;
	bool empty() const;
	Set operator=(const Set& copy);

	friend Set combination(const Set& lhs, const Set& rhs);
	friend Set intersection(const Set& lhs, const Set& rhs);
	friend Set difference(const Set& lhs, const Set& rhs);

private:
	uint16_t getBitIndex(const char& elem) const;
	uint16_t getIndex(const char& elem) const;

	static const uint16_t SIZE = 8;
	static const uint16_t BIT_SIZE = 128 / SIZE;
	uint16_t set[SIZE];
};

