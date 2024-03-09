#include <bits/stdc++.h>
#include "DataVector.h"
#include "VectorDataset.h"

// A function that takes a dataset, a query DataVector object, the number of nearest neighbors to find,
// and the number of DataVector objects in the dataset and outputs the k nearest neighbors
// It uses a vector of pairs to store the distances and indices of the DataVector objects
// It then sorts the vector of pairs and outputs the k nearest neighbors
void knearestneighbors(VectorDataset& dataset, DataVector &query, int k, int n)
{
    std::vector<std::pair<double, int>> distances;

    for (int i = 0; i < n; i++)
    {
        double dist = query.distance(dataset[i]);
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

// A main function that reads the training and test datasets from the csv files
// and outputs the 5 nearest neighbors for 100 random test DataVector objects
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // Measure the time taken to read the datasets
    auto begin = std::chrono::high_resolution_clock::now();

    // Read the training and test datasets
    VectorDataset train_fmnist, test_fmnist;
    train_fmnist.ReadDataset("fmnist-train.csv", 60000, 784);
    test_fmnist.ReadDataset("fmnist-test.csv", 10000, 784);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 

    // Measure the time taken to output the 5 nearest neighbors for 100 random test DataVector objects
    begin = std::chrono::high_resolution_clock::now();
    
    // Output the 5 nearest neighbors for 100 random test DataVector objects
    for(int i=0; i<100; i++)
    {
        int j=rand()%10000;
        cout<<"Nearest neighbors for test vector "<<j<<":\n";
        knearestneighbors(train_fmnist, test_fmnist[j], 5, 60000);
    }
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
}