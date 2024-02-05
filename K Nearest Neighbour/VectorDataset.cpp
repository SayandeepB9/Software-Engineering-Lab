#include "VectorDataset.h"

#include <map>
#include <omp.h>
#include <bits/stdc++.h>
mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

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
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        dataset[i].setDimension(d);
        
        // Debug output
        // cout << "Reading data vector " << i << ": ";

        #pragma omp critical
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

            // Debug output
            // cout << dataset[i][j] << " ";
        }

        // Debug output
        // cout<< i << endl;
    }

    file.close();
}


void VectorDataset::knearestneighbors(DataVector &query, int k, int n)
{
    // Use a vector of pairs instead of a multimap
    std::vector<std::pair<double, int>> distances;

    // Parallelize the loop
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        double dist = query.distance(dataset[i]);

        // Use a critical section to safely update distances
        #pragma omp critical
        distances.push_back(std::make_pair(dist, i));
    }

    // Sort the distances vector
    std::sort(distances.begin(), distances.end());

    // Output the k nearest neighbors
    for (int i = 0; i < std::min(k, n); i++)
    {
        std::cout << distances[i].first << " " << distances[i].second << std::endl;
    }
}