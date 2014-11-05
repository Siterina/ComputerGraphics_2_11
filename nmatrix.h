#ifndef NMATRIX_H
#define NMATRIX_H
#include "nvector.h"
#include <cmath>

class NMatrix
{
public:


    double data[4][4];

    void RotateXZ(double alpha);
    void RotateYZ(double beta);
    void SetScale(double scale, const NVector Scale);
    void RotateAll(double alpha, double beta);

    NMatrix();
    NMatrix(double fill);
    NVector operator*(const NVector v);
    NMatrix operator*(const NMatrix m);
};

#endif // NMATRIX_H
