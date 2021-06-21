
#include "SparseMatrix.h"

// SparseMatrix::Node::Constructor&Destructor

SparseMatrix::Node::Node()
    : row(-1), column(-1), value(0), left(nullptr), up(nullptr)
{   }

SparseMatrix::Node::Node(const int& row, const int& column, const int& value)
    : row(row), column(column), value(value), left(nullptr), up(nullptr)
{   }

SparseMatrix::Node::Node(const Node& copy)
    : row(copy.row), column(copy.column), value(copy.value), left(copy.left), up(copy.up)
{   }

SparseMatrix::Node::~Node()
{   }

// SparseMatrix::Constructors&Destructor

SparseMatrix::SparseMatrix(const int& rows, const int& columns)
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

SparseMatrix::SparseMatrix(const SparseMatrix& copy)
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

SparseMatrix::~SparseMatrix()
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

// SparseMatrix::Methods

void SparseMatrix::add(const int& row, const int& column, const int& value)
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

void SparseMatrix::set(const int& row, const int& column, const int& value)
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

void SparseMatrix::erase(const int& row, const int& column)
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

int SparseMatrix::at(const int& row, const int& column) const
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

int SparseMatrix::getnumRows() const
{
    return this->numRows;
}

int SparseMatrix::getnumColumns() const
{
    return this->numColumns;
}

SparseMatrix SparseMatrix::operator+(const SparseMatrix& rhs)
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
            } else if ((ptrLeft->column > ptrRight->column || ptrRight->column == -1) && ptrLeft->column != -1) {
                newMatrix.add(ptrLeft->row, ptrLeft->column, ptrLeft->value);
                ptrLeft = ptrLeft->left;
            } else {
                newMatrix.add(ptrRight->row, ptrRight->column, ptrRight->value);
                ptrRight = ptrRight->left;
            }
        }
    }

    return newMatrix;
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix& rhs)
{
    if (this->numRows != rhs.numColumns) {
        throw std::exception("The sizes of matrices don't coincide");
    }

    Node* ptrLeft;
    Node* ptrRight;
    SparseMatrix newMatrix(this->numRows, this->numColumns);

    int sum = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numRows; ++j) {
            sum = 0;
            ptrLeft = this->rows[i]->left;
            ptrRight = rhs.columns[j]->up;
            while (ptrLeft->column != -1 || ptrRight->row != -1) {
                if (ptrLeft->column == ptrRight->row) {
                    sum += ptrLeft->value * ptrRight->value;
                    ptrLeft = ptrLeft->left;
                    ptrRight = ptrRight->up;
                } else if ((ptrLeft->column > ptrRight->row || ptrRight->row == -1) && ptrLeft->column != -1) {
                    ptrLeft = ptrLeft->left;
                } else {
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

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& copy)
{
    if (this == &copy) {
        return *this;
    }

    this->numRows = copy.numRows;
    this->numColumns = copy.numColumns;
    delete[] this->rows;
    delete[] this->columns;
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

