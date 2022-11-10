#include "matrix.h"

Matrix::MatrixVector Matrix::createVector(size_t sz, double val)
{
    MatrixVector vec(sz, val);
    return vec;
}

Matrix::Matrix(size_t m, size_t n, double def)
{
    for (size_t i = 0; i < m; i++)
    {
    this->_matrix.push_back(this->createVector(n, def));
    }
}

Matrix::Matrix() { Matrix(0, 0, 0.0); };

void Matrix::resize(size_t m, size_t n, double def)
{
    int rows = this->_matrix.size();
    int cols(0);
    if (rows != 0)
        int cols = this->_matrix[0].size();

    this->_matrix.resize(m);
    for (size_t i = 0; i < m; i++)
    {
        if (i >= rows)
            this->_matrix.push_back(this->createVector(n, def));
        this->_matrix[i].resize(n);
    }
}

Matrix::SizePair Matrix::getSize() const
{
    size_t n_rows = this->_matrix.size();
    size_t n_cols(0);
    if (n_rows != 0)
        size_t n_cols = this->_matrix[0].size();
    return SizePair(n_rows, n_cols);
}

Matrix::MatrixVector& Matrix::operator[](const size_t i)
{
    if (i >= this->_matrix.size())
        throw std::out_of_range("There is no such a row");
    return this->_matrix[i];
}

const Matrix::MatrixVector& Matrix::operator[] (const size_t i) const
{
    if (i >= this->_matrix.size())
        throw std::out_of_range("There is no such a row");
    return this->_matrix[i];
}

double Matrix::getEl(size_t i, size_t j) const
{
    return this->_matrix[i][j];
}

void Matrix::setEl(size_t i, size_t j, double val)
{
    this->_matrix[i][j] = val;
}

bool Matrix::operator == (const Matrix& rhv) const
{
    if (this->getSize() != rhv.getSize())
        return false;
    for (size_t i = 0; i < this->_matrix.size(); i++)
    {
        if (this->_matrix[i] != rhv[i])
            return false;
    }
    return true;
}

bool Matrix::operator != (const Matrix& rhv) const
{
    if (this->getSize() == rhv.getSize())
        return false;
    for (size_t i = 0; i < this->_matrix.size(); i++)
    {
        if (this->_matrix[i] == rhv[i])
            return false;
    }
    return true;
}

Matrix::VectorOfMatrixVector Matrix::operator + (const Matrix& rhv) const
{
    if (this->getSize() != rhv.getSize())
        throw std::invalid_argument("Matrix sizes are incompatible");

    VectorOfMatrixVector new_matrix = this->_matrix;
    for (size_t j = 0; j < this->_matrix.size(); j++)
    {
        for (size_t k = 0; k < this->_matrix[0].size(); k++)
        {
            double val = this->_matrix[j][k] + rhv[j][k];
            new_matrix[j][k] = val;
        }
    }
    return new_matrix;
}

Matrix::VectorOfMatrixVector operator * (const Matrix& lhv, double rhv)
{
    Matrix::VectorOfMatrixVector new_matrix = lhv._matrix;
    Matrix::SizePair sz = lhv.getSize();
    size_t n_rows = sz.first;
    size_t n_cols = sz.second;
    for (size_t j = 0; j < n_rows; j++)
    {
        for (size_t k = 0; k < n_cols; k++)
        {
            double val = lhv[j][k] * rhv;
            new_matrix[j][k] = val;
        }
    }
    return new_matrix;
}

Matrix::VectorOfMatrixVector operator * (double lhv, const Matrix& rhv)
{
    Matrix::VectorOfMatrixVector new_matrix = rhv._matrix;
    Matrix::SizePair sz = rhv.getSize();
    size_t n_rows = sz.first;
    size_t n_cols = sz.second;
    for (size_t j = 0; j < n_rows; j++)
    {
        for (size_t k = 0; k < n_cols; k++)
        {
            double val = rhv[j][k] * lhv;
            new_matrix[j][k] = val;
        }
    }
    return new_matrix;
}
