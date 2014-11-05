#ifndef NMATRIX_H
#define NMATRIX_H
#include "nvector.h"
#include <cmath>

class NMatrix
{
public:


    double data[4][4];

    //void RotateXY(double alpha);
    void RotateXZ(double alpha);
    void RotateYZ(double beta);
    void SetScale(double scale);
    void Move(NVector toMove);

    void RotateAll(double alpha, double beta); // double c);

    NMatrix();
    NMatrix(double fill);
    NVector operator*(const NVector v);
    NMatrix operator*(const NMatrix m);
};

#endif // NMATRIX_H
