#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
    typedef std::vector<double> MatrixVector;
    typedef std::vector<std::vector<double>> VectorOfMatrixVector;
    typedef std::pair<size_t, size_t> SizePair;
    static MatrixVector createVector(size_t sz, double val);

public:
    //constructors
    Matrix(size_t m, size_t n, double def);
    Matrix();

    //methods
    void resize(size_t m, size_t n, double def);
    SizePair getSize() const;
    MatrixVector& operator[] (const size_t i);
    const MatrixVector& operator[] (const size_t i) const;
    double getEl(size_t i, size_t j) const;
    void setEl(size_t i, size_t j, double val);
    bool operator == (const Matrix& rhv) const;
    bool operator != (const Matrix& rhv) const;
    VectorOfMatrixVector operator + (const Matrix& rhv) const;
    friend VectorOfMatrixVector operator * (const Matrix& m, double k);
    friend VectorOfMatrixVector operator * (double k, const Matrix& m);

private:
    //fields
    VectorOfMatrixVector _matrix;
};

//free functions
Matrix::VectorOfMatrixVector operator * (const Matrix& lhv, double rhv);
Matrix::VectorOfMatrixVector operator * (double lhv, const Matrix& rhv);


#endif
