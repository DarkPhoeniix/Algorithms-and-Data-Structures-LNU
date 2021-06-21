#pragma once
#include <cstring>

class String
{
public:
	String()
		: str(nullptr), size(0)
	{	}

	String(const char* str)
		:size(strlen(str))
	{
		this->str = new char[size];
		for (int i = 0; i < size; ++i) {
			this->str[i] = str[i];
		}
	}

	String(const String& copy)
		: size(copy.size)
	{
		this->str = new char[size];
		for (int i = 0; i < size; ++i) {
			this->str[i] = copy.str[i];
		}
	}

	~String()
	{
		if (str != nullptr) {
			delete[] str;
		}
	}

	int length() const
	{
		return this->size;
	}

	void replace(const int& pos, const int& length, const String& str)
	{
		char* newStr = new char[this->size - length + str.length()];
		int x = 0;
		for (int i = 0; i < this->size; ++i) {
			if (i >= pos && i < (pos + length)) {
				for (int j = 0; j < str.length(); ++j) {
					newStr[x++] = str[j];
				}
				i += length - 1;
			}
			else {
				newStr[x++] = this->str[i];
			}
		}
		delete[] this->str;
		this->size = this->size - length + str.length();
		this->str = newStr;
	}

	int find(const String& subStr)
	{
		for (int i = 0, j = 0; i < this->size; ++i) {
			if (this->str[i] == subStr[j]) {
				++j;
				if (j == subStr.length()) {
					return i - j + 1;
				}
			}
			else {
				i -= j;
				j = 0;
			}
		}

		return -1;
	}

	String& operator=(const String& str)
	{
		if (*this == str) {
			return *this;
		}
		else {
			delete this->str;
			this->size = str.size;
			this->str = new char[size];
			for (int i = 0; i < size; ++i) {
				this->str[i] = str[i];
			}
			return *this;
		}
	}

	char& operator[](const int& pos) const
	{
		return this->str[pos];
	}

	friend bool operator==(const String& lhs, const String& rhs)
	{
		if (lhs.length() == rhs.length()) {
			for (int i = 0; i < lhs.length(); ++i) {
				if (lhs[i] != rhs[i]) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}


private:
	char* str;
	int size;
};

