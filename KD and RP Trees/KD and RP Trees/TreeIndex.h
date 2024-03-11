#include <bits/stdc++.h>
using namespace std;

class DataVector
{

private:
    // a vector of double values
    vector<double> v;

public:
    // a constructor that takes an integer argument and initializes the vector to the specified dimension
    DataVector(int dimension = 0);
    // a destructor that clears the vector
    ~DataVector();
    // a copy constructor that takes a DataVector object as an argument
    // and initializes the vector to the same dimension and values
    DataVector(const DataVector &other);
    // an assignment operator that takes a DataVector object as an argument
    // and assigns the vector to the same dimension and values
    DataVector &operator=(const DataVector &other);
    // a member function that takes an integer argument and sets the vector to the specified dimension
    void setDimension(int dimension = 0);
    // a member function that returns the dimension of the vector
    int size();
    // a member function that takes an integer argument and returns the value at the specified index
    double &operator[](int index);
    // a member function that takes a DataVector object as an argument
    // and returns the sum of the two vectors
    DataVector operator+(const DataVector &other);
    // a member function that takes a DataVector object as an argument
    // and returns the difference of the two vectors
    DataVector operator-(const DataVector &other);
    // a member function that takes a DataVector object as an argument
    // and returns the dot product of the two vectors
    double operator*(const DataVector &other);
    // a member function that takes a DataVector object as an argument
    // and returns whether the two vectors are equal
    bool operator==(const DataVector &other);
    // a member function that returns the norm of the vector
    double norm();
    // a member function that takes a DataVector object as an argument
    // and returns the distance between the two vectors
    double distance(const DataVector &other);
};

class VectorDataset
{
    private:
    // a pointer to the entire dataset
    vector<DataVector> dataset;

    public:
        // a constructor that initializes the pointer to NULL
        VectorDataset();
        // a destructor that deletes the dataset
        ~VectorDataset();
        // an operator that takes an integer argument and returns the DataVector object at the specified index
        DataVector &operator[](int index);
        // a member function that takes a filename, the number of DataVector objects, and the dimension of each DataVector object
        // and reads the dataset from the csv file
        void ReadDataset(const char *filename, int n, int d);
        void PrintDataset();
        void AddDataVector(DataVector &dv);
        void DeleteDataVector(int index);
        void DeleteDataVector(DataVector &dv);
        int size();
};


// Minimum number of data points in a leaf node
int MINIMUM_SIZE = 10;

// The data structure which stores the data points
class TreeIndex
{
protected:
    // The dataset which stores the data points
    VectorDataset dataset;
    // The constructor is protected so that the class cannot be instantiated more than once
    TreeIndex() : dataset() {}
    // The destructor is protected
    ~TreeIndex() {}

public:
    // The function to get the instance of the class
    static TreeIndex &GetInstance()
    {
        static TreeIndex instance;
        return instance;
    }
    // The function to read the data from a file
    void ReadData(const char *filename, int n, int d);
};

// The data structure for a node in the KD-Tree
class KDNode
{
private:
    bool leaf; // A flag to indicate if the node is a leaf node
    int axis; // The axis along which the data points are split
    double median; // The median value of the data points along the axis
    KDNode *left, *right, *parent; // The left and right child nodes and the parent node
    vector<int> indices; // The indices of the data points in the node

public:
    // The constructor and destructor
    KDNode() : leaf(false), axis(0), median(0), left(NULL), right(NULL), parent(NULL) {}
    ~KDNode() {}
    // The functions to set and get leaf
    void setLeaf(bool leaf);
    bool isLeaf();
    // The functions to set and get axis
    void setAxis(int axis);
    int getAxis();
    // The functions to set and get median
    void setMedian(double median);
    double getMedian();
    // The functions to set and get left
    void setLeft(KDNode *left);
    KDNode *getLeft();
    // The functions to set and get right
    void setRight(KDNode *right);
    KDNode *getRight();
    // The functions to set and get parent
    void setParent(KDNode *parent);
    KDNode *getParent();
    // The functions to set and get indices
    void setIndices(vector<int> indices);
    vector<int> getIndices();
};

// The data structure for KD-Tree
class KDTreeIndex : public TreeIndex
{
private:
    KDNode *root; // The root node of the KD-Tree
    int no_change_count = 0; // The number of consecutive times the node does not split
    KDTreeIndex() : TreeIndex(), root(NULL) {} // The constructor is private so that the class cannot be instantiated more than once
    ~KDTreeIndex() {} // The destructor is private
    KDNode *searchnode(KDNode *node, DataVector &dv); // A recursive function to search for a node in the KD-Tree

public:
    // The function to get the instance of the class
    static KDTreeIndex &GetInstance()
    {
        static KDTreeIndex instance;
        return instance;
    }
    // The function to choose the axis along which the data points are split
    double ChooseRule(vector<int> &indices, int axis);
    // A recursive function to build the KD-Tree
    KDNode *BuildKDTree(vector<int> &indices, int depth);
    // The function to build the KD-Tree
    void BuildKDTree();
    // The function to read the data from a file
    void ReadData(const char *filename, int n, int d);
    // The function to print the data points
    void PrintData();
    // A recursive function to print the KD-Tree
    void PrintKDTree(KDNode *node);
    // The function to print the KD-Tree
    void PrintKDTree();
    // The function to add a data point to the KD-Tree
    void KDAddDataVector(DataVector &dv);
    // The function to delete a data point from the KD-Tree
    void KDDeleteDataVector(DataVector &dv);
    // The function to get the data points from the indices
    vector<DataVector> getDataVectors(vector<int> indices);
    // A recursive backtracking function to find the k nearest neighbors
    // goes to the leaf node that contains the query point
    // backtracks to the parent node and checks the other child node if necessary
    KDNode *searchKNN(KDNode *node, DataVector &query, int k, priority_queue<pair<double, int>> &neighbors, int &count);
    vector<pair<double, int>> knnSearch(DataVector &query, int k);
};

// The data structure for a node in the RP-Tree
class RPNode
{
private:
    bool leaf; // A flag to indicate if the node is a leaf node
    DataVector axis; // The axis along which the data points are split
    double threshold; // The threshold value of the data points along the axis
    RPNode *left, *right, *parent; // The left and right child nodes and the parent node
    vector<int> indices; // The indices of the data points in the node

public:
    // The constructor and destructor
    RPNode() : leaf(false), axis(0), threshold(0), left(NULL), right(NULL), parent(NULL) {}
    ~RPNode() {}
    // The functions to set and get leaf
    void setLeaf(bool leaf);
    bool isLeaf();
    // The functions to set and get axis
    void setAxis(DataVector axis);
    DataVector getAxis();
    // The functions to set and get threshold
    void setThreshold(double threshold);
    double getThreshold();
    // The functions to set and get left
    void setLeft(RPNode *left);
    RPNode *getLeft();
    // The functions to set and get right
    void setRight(RPNode *right);
    RPNode *getRight();
    // The functions to set and get parent
    void setParent(RPNode *parent);
    RPNode *getParent();
    // The functions to set and get indices
    void setIndices(vector<int> indices);
    vector<int> getIndices();
};

// The data structure for RP-Tree
class RPTreeIndex : public TreeIndex
{
private:
    RPNode *root; // The root node of the RP-Tree
    int no_change_count = 0; // The number of consecutive times the node does not split
    RPTreeIndex() : TreeIndex(), root(NULL) {} // The constructor is private so that the class cannot be instantiated more than once
    ~RPTreeIndex() {} // The destructor is private
    RPNode *searchnode(RPNode *node, DataVector &dv); // A recursive function to search for a node in the RP-Tree

public:
    // The function to get the instance of the class
    static RPTreeIndex &GetInstance()
    {
        static RPTreeIndex instance;
        return instance;
    }
    // The function to choose the axis along which the data points are split
    double ChooseRule(vector<int> &indices, DataVector &axis);
    // A recursive function to build the RP-Tree
    RPNode *BuildRPTree(vector<int> &indices, int depth);
    // The function to build the RP-Tree
    void BuildRPTree();
    // The function to read the data from a file
    void ReadData(const char *filename, int n, int d);
    // The function to print the data points
    void PrintData();
    // A recursive function to print the RP-Tree
    void PrintRPTree(RPNode *node);
    // The function to print the RP-Tree
    void PrintRPTree();
    // The function to add a data point to the RP-Tree
    void RPAddDataVector(DataVector &dv);
    // The function to delete a data point from the RP-Tree
    void RPDeleteDataVector(DataVector &dv);
    // The function to get the data points from the indices
    vector<DataVector> getDataVectors(vector<int> indices);
    // A recursive backtracking function to find the k nearest neighbors
    // goes to the leaf node that contains the query point
    // backtracks to the parent node and checks the other child node if necessary
    RPNode *searchKNN(RPNode *node, DataVector &query, int k, priority_queue<pair<double, int>> &neighbors, int &count);
    vector<pair<double, int>> knnSearch(DataVector &query, int k);
};