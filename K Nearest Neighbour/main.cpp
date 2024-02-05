#include "VectorDataset.cpp"

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    auto begin = std::chrono::high_resolution_clock::now();

    VectorDataset train_fmnist, test_fmnist;
    train_fmnist.ReadDataset("fmnist-train.csv", 60000, 784);
    test_fmnist.ReadDataset("fmnist-test.csv", 10000, 784);

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 

    begin = std::chrono::high_resolution_clock::now();
    
    train_fmnist.knearestneighbors(test_fmnist[0], 5, 60000);
    
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
}