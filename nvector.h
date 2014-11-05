#ifndef NVECTOR_H
#define NVECTOR_H

class NVector
{
public:
    double x, y, z, t;

    void operator=(const NVector v);
    void Move(const NVector toMove);

    NVector();
    NVector(double fill);
    NVector operator+(const NVector v);
    NVector operator-(const NVector v);
};

#endif // NVECTOR_H
