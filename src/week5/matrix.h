#pragma once
#include <iostream>
#include <sstream>
using namespace std;
struct Triple
{
    int row, col, value;
};

class Matrix; // forward declaration

class MatrixNode
{
    friend class Matrix;
    friend istream &operator>>(istream &, Matrix &);       // for reading in a matrix
    friend ostream &operator<<(ostream &, const Matrix &); // for printing a matrix

private:
    MatrixNode *down, *right;
    bool head;
    union
    { // anonymous union
        MatrixNode *next;
        Triple triple;
    };

    MatrixNode(bool b, Triple *t); // constructor
};

MatrixNode::MatrixNode(bool b, Triple *t)
{ // constructor
    head = b;
    if (b)
    {
        right = down = this; // row/column header node
        next = nullptr;
    }
    else
    {
        triple = *t; // element node or header node for list of header nodes
    }
}

class Matrix
{
    friend istream &operator>>(istream &, Matrix &);
    friend ostream &operator<<(ostream &, const Matrix &);

public:
    Matrix() : headnode(nullptr) {}; // constructor
    Matrix(const Matrix &other);     
    ~Matrix();                       // destructor
    MatrixNode *getHeadNode() const { return headnode; }
    Matrix operator+(const Matrix &b) const;
    Matrix operator-(const Matrix &b) const;
    Matrix &operator=(const Matrix &b);

private:
    MatrixNode *headnode;
};

Matrix::Matrix(const Matrix &other) : headnode(nullptr)
{
    if (!other.headnode)
    {
        return; // 空矩阵
    }

    // 复制矩阵的维度信息
    Triple s = other.headnode->triple;
    headnode = new MatrixNode(false, &s);

    int p = max(s.row, s.col);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
    {
        head[i] = new MatrixNode(true, 0);
    }
    MatrixNode **tail = new MatrixNode *[s.col];
    for (int i = 0; i < s.col; i++)
    {
        tail[i] = head[i];
    }

    int currentRow = 0;
    MatrixNode *last = head[0];

    // 遍历原矩阵的所有元素节点
    MatrixNode *otherCurrentHead = other.headnode->right;
    while (otherCurrentHead != other.headnode)
    {
        MatrixNode *otherCurrent = otherCurrentHead->right;
        while (otherCurrent != otherCurrentHead)
        {
            Triple t = otherCurrent->triple;
            if (t.row > currentRow)
            {
                last->right = head[currentRow];
                currentRow = t.row;
                last = head[currentRow];
            }
            tail[t.col] = tail[t.col]->down = last = last->right = new MatrixNode(false, &t);
            otherCurrent = otherCurrent->right;
        }
        otherCurrentHead = otherCurrentHead->next;
    }

    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        tail[i]->down = head[i];
    }

    for (int i = 0; i < p - 1; i++)
    {
        head[i]->next = head[i + 1];
    }
    head[p - 1]->next = headnode;
    headnode->right = head[0];

    delete[] head;
    delete[] tail;
}

// 读入稀疏矩阵
istream &operator>>(istream &is, Matrix &matrix)
{
    // Read in a matrix and set up its linked representation.
    Triple s;
    is >> s.row >> s.col >> s.value; // matrix dimensions
    int p = max(s.row, s.col);

    // set up header node for list of header nodes.
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0)
    {
        matrix.headnode->right = matrix.headnode;
        return is;
    }

    // at least one row or column
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    MatrixNode **tail = new MatrixNode *[s.col];
    for (int i = 0; i < s.col; i++)
        tail[i] = head[i];

    int currentRow = 0;
    MatrixNode *last = head[0]; // last node in current row

    for (int i = 0; i < s.value; i++)
    { // input triples
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow)
        { // close current row
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }
        tail[t.col] = tail[t.col]->down = last = last->right = new MatrixNode(false, &t); // link new node
    }

    last->right = head[currentRow]; // close last row
    for (int i = 0; i < s.col; i++)
        tail[i]->down = head[i]; // close all column lists

    // link the header nodes together
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    matrix.headnode->right = head[0];

    delete[] head;
    delete[] tail;
    return is;
}

// 删除稀疏矩阵
Matrix::~Matrix()
{
    if (!headnode)
        return; // empty matrix
    MatrixNode *currentHead = headnode->right;
    while (currentHead != headnode)
    {
        MatrixNode *current = currentHead->right;
        while (current != currentHead)
        {
            MatrixNode *temp = current;
            current = current->right;
            delete temp;
        }
        MatrixNode *temp = currentHead;
        currentHead = currentHead->next;
        delete temp;
    }
}

ostream &operator<<(ostream &os, const Matrix &matrix)
{
    // Print the matrix in (row, column, value) format.
    if (!matrix.headnode)
    {
        os << "Empty matrix." << endl;
        return os;
    }

    MatrixNode *currentHead = matrix.headnode->right;
    while (currentHead != matrix.headnode)
    {
        MatrixNode *current = currentHead->right;
        while (current != currentHead)
        {
            os << "(" << current->triple.row << ", " << current->triple.col << ", " << current->triple.value << ")" << endl;
            current = current->right;
        }
        currentHead = currentHead->next;
    }
    return os;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    // Assignment operator
    if (this == &other)
        return *this; // self-assignment

    // First, properly delete current matrix
    if (headnode)
    {
        MatrixNode *currentHead = headnode->right;
        while (currentHead != headnode)
        {
            MatrixNode *current = currentHead->right;
            while (current != currentHead)
            {
                MatrixNode *temp = current;
                current = current->right;
                delete temp;
            }
            MatrixNode *temp = currentHead;
            currentHead = currentHead->next;
            delete temp;
        }
        delete headnode;
        headnode = nullptr;
    }

    // Then, copy matrix b
    if (!other.headnode)
        return *this; // empty matrix

    // 复制矩阵的维度信息
    Triple s = other.headnode->triple;
    headnode = new MatrixNode(false, &s);

    int p = max(s.row, s.col);
    MatrixNode **head = new MatrixNode *[p];
    for (int i = 0; i < p; i++)
    {
        head[i] = new MatrixNode(true, 0);
    }
    MatrixNode **tail = new MatrixNode *[s.col];
    for (int i = 0; i < s.col; i++)
    {
        tail[i] = head[i];
    }

    int currentRow = 0;
    MatrixNode *last = head[0];

    // 遍历原矩阵的所有元素节点
    MatrixNode *otherCurrentHead = other.headnode->right;
    while (otherCurrentHead != other.headnode)
    {
        MatrixNode *otherCurrent = otherCurrentHead->right;
        while (otherCurrent != otherCurrentHead)
        {
            Triple t = otherCurrent->triple;
            if (t.row > currentRow)
            {
                last->right = head[currentRow];
                currentRow = t.row;
                last = head[currentRow];
            }
            tail[t.col] = tail[t.col]->down = last = last->right = new MatrixNode(false, &t);
            otherCurrent = otherCurrent->right;
        }
        otherCurrentHead = otherCurrentHead->next;
    }

    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
    {
        tail[i]->down = head[i];
    }

    for (int i = 0; i < p - 1; i++)
    {
        head[i]->next = head[i + 1];
    }
    head[p - 1]->next = headnode;
    headnode->right = head[0];

    delete[] head;
    delete[] tail;
    return *this;
}