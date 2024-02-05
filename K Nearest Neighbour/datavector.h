#ifndef DATAVECTOR_H
#define DATAVECTOR_H

#include <vector>
class DataVector
{
    std::vector<double> v;

public:
    DataVector(int dimension = 0);
    ~DataVector();
    DataVector(const DataVector &other);
    DataVector &operator=(const DataVector &other);
    void setDimension(int dimension = 0);
    int size();
    double &operator[](int index);
    DataVector operator+(const DataVector &other);
    DataVector operator-(const DataVector &other);
    double operator*(const DataVector &other);
    double norm();
    double distance(const DataVector &other);
};

#endif // DATAVECTOR_H
