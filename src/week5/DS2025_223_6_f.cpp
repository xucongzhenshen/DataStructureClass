#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include "matrix.h"
using namespace std;

Matrix Matrix::operator+(const Matrix &b) const
{
    if (!headnode || !b.headnode)
    {
        throw invalid_argument("One of the matrices is empty.");
    }
    MatrixNode *currentHead = headnode->right;
    MatrixNode *bCurrentHead = b.headnode->right;
    Matrix result;
    auto t = this->headnode->triple;
    Triple s = b.headnode->triple;
    Triple resTriple{};
    resTriple.row = max(t.row, s.row);
    resTriple.col = max(t.col, s.col);
    resTriple.value = 0;
    result.headnode = new MatrixNode(false, &resTriple);
    int nonZeroCount = 0;

    // initialize result matrix
    MatrixNode **head = new MatrixNode *[resTriple.row];
    for (int i = 0; i < resTriple.row; i++)
    {
        head[i] = new MatrixNode(true, 0);
    }
    MatrixNode **tail = new MatrixNode *[resTriple.col];
    for (int i = 0; i < resTriple.col; i++)
    {
        tail[i] = head[i];
    }

    // iterator initialization
    MatrixNode *current = currentHead->right;
    MatrixNode *bCurrent = bCurrentHead->right;
    MatrixNode *last = head[0];
    int currentRow = 0;

    // traverse both matrices
    while (currentHead != headnode && bCurrentHead != b.headnode)
    {
        if (current->triple.row < bCurrent->triple.row ||
            (current->triple.row == bCurrent->triple.row && current->triple.col < bCurrent->triple.col))
        {
            // current matrix has smaller element
            if (current->triple.row > currentRow)
            { // close current row
                last->right = head[currentRow];
                currentRow = current->triple.row;
                last = head[currentRow];
            }
            tail[current->triple.col] = tail[current->triple.col]->down = last = last->right = new MatrixNode(false, &current->triple);

            // advance current matrix iterator
            current = current->right;
            while (currentHead == current)
            {
                currentHead = currentHead->next;
                current = currentHead->right;
            }
        }
        else if (bCurrent->triple.row < current->triple.row ||
                 (bCurrent->triple.row == current->triple.row && bCurrent->triple.col < current->triple.col))
        {
            // b matrix has smaller element
            if (bCurrent->triple.row > currentRow)
            { // close current row
                last->right = head[currentRow];
                currentRow = bCurrent->triple.row;
                last = head[currentRow];
            }
            tail[bCurrent->triple.col] = tail[bCurrent->triple.col]->down = last = last->right = new MatrixNode(false, &bCurrent->triple);

            // advance b matrix iterator
            bCurrent = bCurrent->right;
            while (bCurrentHead == bCurrent)
            {
                bCurrentHead = bCurrentHead->next;
                bCurrent = bCurrentHead->right;
            }
        }
        else
        {
            // same position, add values
            int summedValue = current->triple.value + bCurrent->triple.value;
            if (summedValue != 0)
            {
                Triple newTriple = {current->triple.row, current->triple.col, summedValue};
                if (newTriple.row > currentRow)
                { // close current row
                    last->right = head[currentRow];
                    currentRow = newTriple.row;
                    last = head[currentRow];
                }
                tail[newTriple.col] = tail[newTriple.col]->down = last = last->right = new MatrixNode(false, &newTriple);
            }
            // advance both iterators
            current = current->right;
            while (currentHead == current)
            {
                currentHead = currentHead->next;
                current = currentHead->right;
            }
            bCurrent = bCurrent->right;
            while (bCurrentHead == bCurrent)
            {
                bCurrentHead = bCurrentHead->next;
                bCurrent = bCurrentHead->right;
            }
        }
        resTriple.value++;
    }
    // process remaining elements
    MatrixNode *remainingHead = currentHead == headnode ? bCurrentHead : currentHead;
    MatrixNode *remainingCurrent = currentHead == headnode ? bCurrent : current;
    while (remainingHead != (currentHead == headnode ? b.headnode : headnode))
    {
        if (remainingCurrent->triple.row > currentRow)
        { // close current row
            last->right = head[currentRow];
            currentRow = remainingCurrent->triple.row;
            last = head[currentRow];
        }
        tail[remainingCurrent->triple.col] = tail[remainingCurrent->triple.col]->down = last = last->right = new MatrixNode(false, &remainingCurrent->triple);

        // advance remaining iterator
        remainingCurrent = remainingCurrent->right;
        while (remainingHead == remainingCurrent)
        {
            remainingHead = remainingHead->next;
            remainingCurrent = remainingHead->right;
        }

        resTriple.value++;
    }
    last->right = head[currentRow]; // close last row
    for (int i = 0; i < resTriple.col; i++)
        tail[i]->down = head[i]; // close all column lists
    // link the header nodes together
    for (int i = 0; i < resTriple.row - 1; i++)
        head[i]->next = head[i + 1];

    head[resTriple.row - 1]->next = result.headnode;
    result.headnode->right = head[0];
    delete[] head;
    delete[] tail;
    return result;
}

int main()
{
    Matrix m1, m2, m3;
    std::istringstream input1("2 2 2\n0 0 1\n1 1 2\n");
    input1 >> m1;
    cout << "Matrix m1:" << endl;
    cout << m1;

    std::istringstream input2("2 2 2\n0 1 3\n1 0 4\n");
    input2 >> m2;
    cout << "Matrix m2:" << endl;
    cout << m2;

    ostringstream output;
    cout << "Matrix m3 (m1 + m2):" << endl;
    m3 = m1 + m2;
    cout << m3;
    output << m3;
    assert(output.str() == "(0, 0, 1)\n(0, 1, 3)\n(1, 0, 4)\n(1, 1, 2)\n");
    return 0;
}
