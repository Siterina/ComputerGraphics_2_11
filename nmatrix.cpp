#include "nmatrix.h"

NMatrix::NMatrix() {
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(i == j)
                data[i][j] = 1;
            else data[i][j] = 0;
}

NMatrix :: NMatrix(double fill){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            data[i][j] = fill;
}

NVector NMatrix::operator*(const NVector v) {

    NVector result = NVector(0);

    result.x = data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z + data[0][3] * v.t;
    result.y = data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z + data[1][3] * v.t;
    result.z = data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z + data[2][3] * v.t;
    result.t = data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z + data[3][3] * v.t;
    return result;
}


NMatrix NMatrix::operator*(const NMatrix m) {
    NMatrix result = NMatrix(0);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                result.data[i][j] += data[i][k] * m.data[k][j];

    return result;
}


void NMatrix::RotateXZ(double alpha) {
    data[0][0] = cos(alpha);
    data[0][2] = sin(alpha);
    data[2][0] = -sin(alpha);
    data[2][2] = cos(alpha);
}

void NMatrix::RotateYZ(double beta) {
    data[1][1] = cos(beta);
    data[1][2] = -sin(beta);
    data[2][1] = sin(beta);
    data[2][2] = cos(beta);
}

void NMatrix::SetScale(double K, const NVector Scale) {
    data[0][0] = K * Scale.x;
    data[1][1] = K * Scale.y;
    data[2][2] = K * Scale.z;
}

/*void NMatrix::Move(const NVector toMove) {
    data[0][0] = toMove.x;
    data[1][1] = toMove.y;
    data[2][3] = toMove.z;
}*/


void NMatrix::RotateAll(double alpha, double beta) { // double c);
    NMatrix result = NMatrix();
    NMatrix XZ = NMatrix();
    NMatrix YZ = NMatrix();
    XZ.RotateXZ(alpha);
    YZ.RotateYZ(beta);
    result = XZ * YZ;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            data[i][j] = result.data[i][j];
}



