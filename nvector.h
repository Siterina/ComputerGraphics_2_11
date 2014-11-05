#ifndef NVECTOR_H
#define NVECTOR_H

class NVector
{
public:
    double x, y, z, t;
    NVector();
    NVector(double fill);
    NVector operator+(const NVector v);
    NVector operator-(const NVector v);
    void operator=(const NVector v);

   // NVector VectorComposition(const NVector a, const NVector b);
   // double ScalarComposition(const NVector a, const NVector b);
};

#endif // NVECTOR_H
