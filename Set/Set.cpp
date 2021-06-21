
#include "Set.h"

// Private
// METHODS

uint16_t Set::getIndex(const char& elem) const
{
	return elem % this->SIZE;
}

uint16_t Set::getBitIndex(const char& elem) const
{
	return elem % this->BIT_SIZE;
}

// Public
// CONSTRUCTOR

Set::Set()
	: set{0}
{	}

Set::Set(const Set& copy)
{
	for (int i = 0; i < this->SIZE; ++i) {
		this->set[i] = copy.set[i];
	}
}

// METHODS

void Set::add(const char& elem)
{
	this->set[getIndex(elem)] |= 1 << getBitIndex(elem);
}

void Set::remove(const char& elem)
{
	this->set[getIndex(elem)] &= ~(1 << getBitIndex(elem));
}

bool Set::isInSet(const char& elem) const
{
	return this->set[getIndex(elem)] & (1 << getBitIndex(elem));
}

bool Set::empty() const
{
	for (int i = 0; i < this->SIZE; ++i) {
		for (int j = 0; j < this->BIT_SIZE; ++j) {
			if (this->set[i] >> j) {
				return false;
			}
		}
	}
	return true;
}

Set Set::operator=(const Set& copy)
{
	for (int i = 0; i < this->SIZE; ++i) {
		this->set[i] = copy.set[i];
	}
	return *this;
}

// FRIEND FUNCTIONS

Set combination(const Set& lhs, const Set& rhs)
{
	Set result;
	for (int i = 0; i < result.SIZE; ++i) {
		result.set[i] = lhs.set[i] | rhs.set[i];
	}
	return result;
}

Set intersection(const Set& lhs, const Set& rhs)
{
	Set result;
	for (int i = 0; i < result.SIZE; ++i) {
		result.set[i] = lhs.set[i] & rhs.set[i];
	}
	return result;
}

Set difference(const Set& lhs, const Set& rhs)
{
	Set result;
	for (int i = 0; i < result.SIZE; ++i) {
		result.set[i] = lhs.set[i] & ~(rhs.set[i]);
	}
	return result;
}

