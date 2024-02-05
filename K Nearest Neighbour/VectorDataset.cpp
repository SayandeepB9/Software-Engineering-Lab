#include <bits/stdc++.h>
#include "DataVector.h"
#include "VectorDataset.h"

using namespace std;
VectorDataset::VectorDataset()
{
    dataset = NULL;
}

VectorDataset::~VectorDataset()
{
    if (dataset != NULL)
    {
        delete[] dataset;
    }
}

DataVector &VectorDataset::operator[](int index)
{
    return dataset[index];
}

void VectorDataset::ReadDataset(const char *filename, int n, int d)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }

    dataset = new DataVector[n];
    for (int i = 0; i < n; i++)
    {
        dataset[i].setDimension(d);
 
        for (int j = 0; j < d; j++)
        {
            if (!(file >> dataset[i][j]))
            {
                cerr << "Error reading value at line " << i + 1 << ", position " << j + 1 << endl;
                exit(1);
            }

            if (j < d - 1)
            {
                if (file.peek() == ',')
                {
                    file.ignore();
                }
                else
                {
                    cerr << "Expected comma at line " << i + 1 << ", position " << j + 1 << endl;
                    exit(1);
                }
            }
        }
    }

    file.close();
}