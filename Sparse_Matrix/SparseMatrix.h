#pragma once
#include <iostream>
#include <sstream>

class SparseMatrix
{
public:
	SparseMatrix(const int& rows, const int& columns);
	SparseMatrix(const SparseMatrix& copy);
	~SparseMatrix();

	void add(const int& row, const int& column, const int& value);
	void set(const int& row, const int& column, const int& value);
	void erase(const int& row, const int& column);
	int at(const int& row, const int& column) const;
	int getnumRows() const;
	int getnumColumns() const;

	SparseMatrix operator+(const SparseMatrix& rhs);
	SparseMatrix operator*(const SparseMatrix& rhs);
	SparseMatrix& operator=(const SparseMatrix& copy);

private:
	class Node
	{
	public:
		Node();
		Node(const int& row, const int& column, const int& value);
		Node(const Node& copy);
		~Node();

		int row;
		int column;
		int value;
		Node* left;
		Node* up;
	};

    int numRows;
    int numColumns;
	Node** rows;
	Node** columns;
};
