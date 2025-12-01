#include "matrix.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cassert>
using namespace std;

Matrix Matrix::operator*(const Matrix &b) const
{
    if (!headnode || !b.headnode)
    {
        throw invalid_argument("One of the matrices is empty.");
    }
    MatrixNode *aRowHead = headnode->right;
    MatrixNode *bColHead = b.headnode->right;
    Triple aSize = headnode->triple;
    Triple bSize = b.headnode->triple;

    if (aSize.col != bSize.row)
    {
        throw invalid_argument("Incompatible matrix dimensions for multiplication.");
    }

    Triple resTriple{};
    resTriple.row = aSize.row;
    resTriple.col = bSize.col;
    resTriple.value = 0;
    Matrix result;
    result.headnode = new MatrixNode(false, &resTriple);
    if(resTriple.row == 0 || resTriple.col == 0)
        return result;

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

    // Perform multiplication
    MatrixNode *last = head[0];
    for (int i = 0; i < aSize.row; ++i)
    {
        bColHead = b.headnode->right;
        for (int j = 0; j < bSize.col; ++j)
        {
            MatrixNode *aCurrent = aRowHead->right;
            MatrixNode *bCurrentIter = bColHead->down;
            int sum = 0;
            while (aCurrent != aRowHead && bCurrentIter != bColHead)
            {
                if (aCurrent->triple.col < bCurrentIter->triple.row)
                {
                    aCurrent = aCurrent->right;
                }
                else if (aCurrent->triple.col > bCurrentIter->triple.row)
                {
                    bCurrentIter = bCurrentIter->down;
                }
                else
                {
                    sum += aCurrent->triple.value * bCurrentIter->triple.value;
                    aCurrent = aCurrent->right;
                    bCurrentIter = bCurrentIter->down;
                }
            }
            if (sum != 0)
            {
                Triple newTriple{i, j, sum};
                if (i > last->triple.row)
                { // close current row
                    last->right = head[last->triple.row];
                    last = head[i]; 
                }
                tail[newTriple.col] = tail[newTriple.col]->down = last = last->right = new MatrixNode(false, &newTriple);
                resTriple.value++;
            }
            bColHead = bColHead->next;
        }
        aRowHead = aRowHead->next;
    }
    // close last row
    last->right = head[last->triple.row];
    for (int i = 0; i < resTriple.col; i++)
    {
        tail[i]->down = head[i];
    }
    for(int i = 0; i < resTriple.row - 1; i++)
    {
        head[i]->next = head[i + 1];
    }
    result.headnode->right = head[0];
    head[resTriple.row - 1]->next = result.headnode;
    delete[] head;
    delete[] tail;
    return std::move(result);
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
    cout << "Matrix m3 (m1 * m2):" << endl;
    m3 = m1 * m2;
    cout << m3;
    output << m3;
    assert(output.str() == "(0, 1, 3)\n(1, 0, 8)\n");
    return 0;
}