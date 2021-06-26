
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "CppUnitTest.h"



class SparseMatrix
{
public:
	SparseMatrix(const int& rows, const int& columns)
		: numRows(rows), numColumns(columns)
	{
		this->rows = new Node * [numRows];
		this->columns = new Node * [numColumns];

		for (int i = 0; i < numRows; ++i) {
			this->rows[i] = new Node();
			this->rows[i]->left = this->rows[i];
		}
		for (int i = 0; i < numColumns; ++i) {
			this->columns[i] = new Node();
			this->columns[i]->up = this->columns[i];
		}
	}
	SparseMatrix(const SparseMatrix& copy)
		: numRows(copy.numRows), numColumns(copy.numColumns)
	{
		this->rows = new Node * [numRows];

		this->columns = new Node * [numColumns];

		for (int i = 0; i < numRows; ++i) {
			this->rows[i] = new Node();
			this->rows[i]->left = this->rows[i];
		}
		for (int i = 0; i < numColumns; ++i) {
			this->columns[i] = new Node();
			this->columns[i]->up = this->columns[i];
		}
		for (int i = 0; i < numRows; i++) {
			Node* current = copy.rows[i];
			while (current->left != copy.rows[i]) {
				current = current->left;
				this->add(current->row, current->column, current->value);
			}
		}
	}
	~SparseMatrix()
	{
		for (int i = 0; i < numRows; i++) {
			Node* current = this->rows[i]->left;
			Node* nodeToDel = current;
			while (current != nullptr && current != this->rows[i]) {
				nodeToDel = current;
				current = current->left;
				delete nodeToDel;
			}
		}
		for (int i = 0; i < numRows; ++i) {
			delete rows[i];
		}
		for (int i = 0; i < numColumns; ++i) {
			delete columns[i];
		}

		delete[] rows;
		delete[] columns;
	}

	void add(const int& row, const int& column, const int& value)
	{
		if (value == 0) {
			return;
		}
		else if (row >= numRows || row < 0 || column >= numColumns || column < 0) {
			throw std::exception("Wrong index");
			return;
		}

		Node* nodeToCreate = new Node(row, column, value);
		Node* prevNode = this->rows[row];

		while (prevNode->left->column > column) {
			prevNode = prevNode->left;
		}
		if (prevNode->left->column == column) {
			delete nodeToCreate;
			throw std::exception("This element is already exist");
		}

		nodeToCreate->left = prevNode->left;
		prevNode->left = nodeToCreate;
		prevNode = this->columns[column];

		while (prevNode->up->row > row) {
			prevNode = prevNode->up;
		}

		nodeToCreate->up = prevNode->up;
		prevNode->up = nodeToCreate;
	}
	void set(const int& row, const int& column, const int& value)
	{
		if (value == 0) {
			return;
		}

		Node* prevNode = this->rows[row];

		while (prevNode->left->column > column) {
			prevNode = prevNode->left;
		}

		prevNode->left->value = value;
	}
	void erase(const int& row, const int& column)
	{
		if (row >= numRows || row < 0 || column >= numColumns || column < 0) {
			throw std::exception("Wrong index");
		}

		Node* delNode;
		Node* prev = this->rows[row];

		while (prev->left->column > column) {
			prev = prev->left;
		}
		if (prev->left->column != column) {
			return;
		}

		delNode = prev->left;
		prev->left = delNode->left;

		prev = this->columns[column];

		while (prev->up->row > row) {
			prev = prev->up;
		}
		delNode = prev->up;
		prev->up = delNode->up;
		delete delNode;
	}
	int at(const int& row, const int& column) const
	{
		if (row >= numRows || row < 0 || column >= numColumns || column < 0) {
			throw std::exception("Wrong index");
		}

		Node* current = this->rows[row];
		while (current->left->column > column) {
			current = current->left;
		}
		current = current->left;
		if (current->column != column) {
			return 0;
		}

		return current->value;
	}
	int getnumRows() const
	{
		return this->numRows;
	}
	int getnumColumns() const
	{
		return this->numColumns;
	}

	SparseMatrix operator+(const SparseMatrix& rhs)
	{
		if (this->numRows != rhs.numRows || this->numColumns != rhs.numColumns) {
			throw std::exception("The sizes of matrices don't coincide");
		}

		Node* ptrLeft;
		Node* ptrRight;
		SparseMatrix newMatrix(this->numRows, this->numColumns);

		for (int i = 0; i < numRows; ++i) {
			ptrLeft = this->rows[i]->left;
			ptrRight = rhs.rows[i]->left;
			while (ptrLeft->column != -1 || ptrRight->column != -1) {
				if (ptrLeft->column == ptrRight->column) {
					newMatrix.add(ptrLeft->row, ptrLeft->column, ptrLeft->value + ptrRight->value);
					ptrLeft = ptrLeft->left;
					ptrRight = ptrRight->left;
				}
				else if ((ptrLeft->column > ptrRight->column || ptrRight->column == -1) && ptrLeft->column != -1) {
					newMatrix.add(ptrLeft->row, ptrLeft->column, ptrLeft->value);
					ptrLeft = ptrLeft->left;
				}
				else {
					newMatrix.add(ptrRight->row, ptrRight->column, ptrRight->value);
					ptrRight = ptrRight->left;
				}
			}
		}

		return newMatrix;
	}
	SparseMatrix operator*(const SparseMatrix& rhs)
	{
		if (this->numRows != rhs.numColumns) {
			throw std::exception("The sizes of matrices don't coincide");
		}

		Node* ptrLeft;
		Node* ptrRight;
		SparseMatrix newMatrix(this->numRows, rhs.numColumns);

		int sum = 0;
		for (int i = 0; i < this->numRows; ++i) {
			for (int j = 0; j < rhs.numColumns; ++j) {
				sum = 0;
				ptrLeft = this->rows[i]->left;
				ptrRight = rhs.columns[j]->up;
				while (ptrLeft->column != -1 || ptrRight->row != -1) {
					if (ptrLeft->column == ptrRight->row) {
						sum += ptrLeft->value * ptrRight->value;
						ptrLeft = ptrLeft->left;
						ptrRight = ptrRight->up;
					}
					else if ((ptrLeft->column > ptrRight->row || ptrRight->row == -1) && ptrLeft->column != -1) {
						ptrLeft = ptrLeft->left;
					}
					else {
						ptrRight = ptrRight->up;
					}
				}
				if (sum != 0) {
					newMatrix.add(i, j, sum);
				}
			}
		}

		return newMatrix;
	}
	SparseMatrix& operator=(const SparseMatrix& copy)
	{
		if (this == &copy) {
			return *this;
		}
		this->~SparseMatrix();
		this->numRows = copy.numRows;
		this->numColumns = copy.numColumns;

		this->rows = new Node * [numRows];
		this->columns = new Node * [numColumns];

		for (int i = 0; i < numRows; ++i) {
			this->rows[i] = new Node();
			this->rows[i]->left = this->rows[i];
		}
		for (int i = 0; i < numColumns; ++i) {
			this->columns[i] = new Node();
			this->columns[i]->up = this->columns[i];
		}
		for (int i = 0; i < numRows; i++) {
			Node* current = copy.rows[i];
			while (current->left != copy.rows[i]) {
				current = current->left;
				this->add(current->row, current->column, current->value);
			}
		}

		return *this;
	}

private:
	class Node
	{
	public:
		Node()
			: row(-1), column(-1), value(0), left(nullptr), up(nullptr)
		{   }
		Node(const int& row, const int& column, const int& value)
			: row(row), column(column), value(value), left(nullptr), up(nullptr)
		{   }
		Node(const Node& copy)
			: row(copy.row), column(copy.column), value(copy.value), left(copy.left), up(copy.up)
		{   }
		~Node()
		{   }

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



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{
	TEST_CLASS(Test_SparseMatrix)
	{
	public:
		TEST_METHOD(TestAdd)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			try {
				SparseMatrix m(3, 3);

				m.add(0, 0, 11);
				m.add(1, 1, 22);
				m.add(2, 2, 33);

				Assert::AreEqual(11, m.at(0, 0));
				Assert::AreEqual(22, m.at(1, 1));
				Assert::AreEqual(33, m.at(2, 2));

				m.add(1, 1, 222);
			}
			catch (std::exception& ex) {
				std::string err = ex.what();
				Assert::AreEqual(err, std::string("This element is already exist"));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestErase)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			try {
				SparseMatrix m(3, 3);

				m.add(0, 0, 11);
				m.add(1, 1, 22);
				m.add(2, 2, 33);
				m.add(1, 2, 23);

				m.erase(1, 1);
				Assert::AreEqual(0, m.at(1, 1));
				m.erase(1, 1);
				Assert::AreEqual(0, m.at(1, 1));
				m.erase(2, 4);
			}
			catch (std::exception& ex) {
				std::string err = ex.what();
				Assert::AreEqual(err, std::string("Wrong index"));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestGetters)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			{
				SparseMatrix m(3, 4);
				Assert::AreEqual(3, m.getnumRows());
				Assert::AreEqual(4, m.getnumColumns());
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestConstructorCopy)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			{
				SparseMatrix m1(3, 5);
				m1.add(1, 2, 23);
				m1.add(2, 4, 35);
				m1.add(0, 0, 11);
				SparseMatrix m2 = m1;
				Assert::AreEqual(23, m2.at(1, 2));
				Assert::AreEqual(35, m2.at(2, 4));
				Assert::AreEqual(11, m2.at(0, 0));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestAssignmentOperator)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			{
				SparseMatrix m1(3, 5);
				m1.add(1, 2, 23);
				m1.add(2, 4, 35);
				m1.add(0, 0, 11);
				SparseMatrix m2(2, 2);
				m2 = m1;
				Assert::AreEqual(23, m2.at(1, 2));
				Assert::AreEqual(35, m2.at(2, 4));
				Assert::AreEqual(11, m2.at(0, 0));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestAddition)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			try {
				SparseMatrix m1(3, 3);
				SparseMatrix m2(3, 3);
				m1.add(1, 2, 23);
				m1.add(2, 0, 31);
				m1.add(0, 0, 11);
				m2.add(1, 2, 23);
				m2.add(1, 0, 21);
				SparseMatrix m3 = m1 + m2;
				Assert::AreEqual(11, m3.at(0, 0));
				Assert::AreEqual(21, m3.at(1, 0));
				Assert::AreEqual(46, m3.at(1, 2));
				Assert::AreEqual(31, m3.at(2, 0));
				SparseMatrix m4(3, 4);
				m4.add(2, 3, 34);
				m4.add(1, 1, 22);
				m3 = m1 + m4;
			}
			catch (std::exception& ex) {
				std::string s = ex.what();
				Assert::AreEqual(s, std::string("The sizes of matrices don't coincide"));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

		TEST_METHOD(TestMultiplication)
		{
			_CrtMemState s1, s2, s3;
			_CrtMemCheckpoint(&s1);
			try {
				SparseMatrix m1(2, 3);
				SparseMatrix m2(3, 4);
				m2.add(1, 3, 24);
				m2.add(2, 0, 31);
				m2.add(0, 0, 11);
				m1.add(1, 2, 23);
				m1.add(1, 0, 21);
				SparseMatrix m3 = m1 * m2;
				Assert::AreEqual(944, m3.at(1, 0));
				SparseMatrix m4(3, 4);
				m4.add(2, 3, 34);
				m4.add(1, 1, 22);
				m3 = m1 * m4;



				SparseMatrix m_1(3, 3);
				SparseMatrix m_2(3, 3);

				m_1.add(0, 0, 11);
				m_1.add(1, 2, 23);
				m_1.add(2, 1, 32);
				m_1.add(1, 1, 22);
				m_2.add(0, 0, 11);
				m_2.add(1, 1, 22);
				m_2.add(2, 1, 32);
				m_2.add(2, 2, 33);

				SparseMatrix result1(4, 4);
				result1 = m_1 * m_2;
				Assert::AreEqual(121, result1.at(0, 0));
				Assert::AreEqual(1220, result1.at(1, 1));
				Assert::AreEqual(759, result1.at(1, 2));
				Assert::AreEqual(704, result1.at(2, 1));
			}
			catch (std::exception& ex) {
				std::string s = ex.what();
				Assert::AreEqual(s, std::string("The sizes of matrices don't coincide"));
			}
			_CrtMemCheckpoint(&s2);

			if (_CrtMemDifference(&s3, &s1, &s2))
			{
				_CrtMemDumpStatistics(&s3);
				Assert::Fail();
			}
		}

	};
}
