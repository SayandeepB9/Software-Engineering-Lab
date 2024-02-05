#ifndef VECTOR_DATASET_H
#define VECTOR_DATASET_H

#include "datavector.cpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class VectorDataset
{
    DataVector *dataset;

    public:
        VectorDataset();
        ~VectorDataset();
        DataVector &operator[](int index);
        void ReadDataset(const char *filename, int n, int d);
        void knearestneighbors(DataVector &query, int k, int n);
};

#endif // VECTOR_DATASET_H