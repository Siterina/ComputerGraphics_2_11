#include "nvector.h"

NVector::NVector()
{
    x = 0; y = 0; z = 0; t = 1;
}
NVector::NVector(double fill) {
    x = fill; y = fill; z = fill; t = 1;
}

NVector NVector::operator+(const NVector v) {
    NVector result = NVector();
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    result.t = t + v.t;
    return result;
}

NVector NVector::operator-(const NVector v) {
    NVector result = NVector();
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    result.t = t - v.t;
    return result;
}

void NVector::operator=(const NVector v) {
    x = v.x; y = v.y; z = v.z; t = v.t;
}

