#include <iostream>
#include <vector>

// Structure to represent a non-zero element in a sparse matrix
struct Triple
{
    int row;
    int col;
    int value;
};

// Class to represent a sparse matrix
class SparseMatrix
{
    int rows;
    int cols;
    int terms;
    std::vector<Triple> data;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), terms(0) {}

    void addTerm(int r, int c, int v)
    {
        if (v != 0)
        {
            data.push_back({r, c, v});
            ++terms;
        }
    }

    void print() const
    {
        std::cout << "Sparse Matrix: " << rows << "x" << cols << " with " << terms << " non-zero terms\n";
        for (const auto &t : data)
        {
            std::cout << "(" << t.row << ", " << t.col << ") = " << t.value << "\n";
        }
    }

    // Function to perform fast transpose of the sparse matrix
    SparseMatrix fastTranspose() const
    {
        SparseMatrix transposed(cols, rows);
        if (terms == 0)
            return transposed;

        std::vector<int> rowS(cols + 1, 0);
        for (const auto &t : data)
            ++rowS[t.col + 1];

        for (int i = 1; i < cols; ++i)
            rowS[i] += rowS[i - 1];

        transposed.data.resize(terms);
        for (const auto &t : data)
        {
            int pos = rowS[t.col]++;
            transposed.data[pos] = {t.col, t.row, t.value};
        }
        transposed.terms = terms;
        return transposed;
    }
};
int main()
{
    // Example usage
    SparseMatrix sm(6, 5);
    sm.addTerm(0, 1, 5);
    sm.addTerm(0, 4, 7);
    sm.addTerm(1, 0, 3);
    sm.addTerm(2, 3, 8);
    sm.addTerm(3, 0, 6);
    sm.addTerm(3, 4, 6);
    sm.addTerm(5, 2, 9);

    sm.print();

    SparseMatrix transposed = sm.fastTranspose();
    transposed.print();

    return 0;
}