#include "TreeIndex.h"

DataVector::DataVector(int dimension)
{
    v.resize(dimension);
}

DataVector::~DataVector()
{
    v.clear();
}

DataVector::DataVector(const DataVector &other)
{
    v = other.v;
}

DataVector &DataVector::operator=(const DataVector &other)
{
    v = other.v;
    return *this;
}

void DataVector::setDimension(int dimension)
{
    v.clear();
    v.resize(dimension);
}

int DataVector::size()
{
    return v.size();
}

double &DataVector::operator[](int index)
{
    return v[index];
}

DataVector DataVector::operator+(const DataVector &other)
{
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result.v[i] = v[i] + other.v[i];
    }
    return result;
}

DataVector DataVector::operator-(const DataVector &other)
{
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++)
    {
        result.v[i] = v[i] - other.v[i];
    }
    return result;
}

double DataVector::operator*(const DataVector &other)
{
    double result = 0;
    for (int i = 0; i < v.size(); i++)
    {
        result += v[i] * other.v[i];
    }
    return result;
}

bool DataVector::operator==(const DataVector &other)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] != other.v[i])
        {
            return false;
        }
    }
    return true;
}

double DataVector::norm()
{
    double result = 0;
    for (int i = 0; i < v.size(); i++)
    {
        result += v[i] * v[i];
    }
    return sqrt(result);
}

double DataVector::distance(const DataVector &other)
{
    DataVector diff = *this - other;
    return diff.norm();
}

VectorDataset::VectorDataset()
{
    dataset.clear();
}

VectorDataset::~VectorDataset()
{
    if (dataset.size() > 0)
    {
        dataset.clear();
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

    DataVector dv(d);
    for (int i = 0; i < n; i++)
    {
        
        for (int j = 0; j < d; j++)
        {
            if (!(file >> dv[j]))
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
        dataset.push_back(dv);
    }

    file.close();
}

void VectorDataset::PrintDataset()
{
    for (int i = 0; i < dataset.size(); i++)
    {
        cout << "DataVector " << i << ": ";
        for (int j = 0; j < dataset[i].size(); j++)
        {
            cout << dataset[i][j] << " ";
        }
        cout << endl;
    }
}

void VectorDataset::AddDataVector(DataVector &dv)
{
    dataset.push_back(dv);
}

void VectorDataset::DeleteDataVector(int index)
{
    dataset.erase(dataset.begin() + index);
}

void VectorDataset::DeleteDataVector(DataVector &dv)
{
    for (int i = 0; i < dataset.size(); i++)
    {
        if (dataset[i] == dv)
        {
            dataset.erase(dataset.begin() + i);
            break;
        }
    }
    cout << "DataVector not found" << endl;
}

int VectorDataset::size()
{
    return dataset.size();
}

void TreeIndex::ReadData(const char *filename, int n, int d)
{
    dataset.ReadDataset(filename, n, d);
}

void KDNode::setLeaf(bool leaf)
{

    this->leaf = leaf;
}
bool KDNode::isLeaf()
{

    return leaf;
}
void KDNode::setAxis(int axis)
{

    this->axis = axis;
}
int KDNode::getAxis()
{

    return axis;
}
void KDNode::setMedian(double median)
{

    this->median = median;
}
double KDNode::getMedian()
{

    return median;
}
void KDNode::setLeft(KDNode *left)
{

    this->left = left;
}
KDNode *KDNode::getLeft()
{

    return left;
}
void KDNode::setRight(KDNode *right)
{

    this->right = right;
}
KDNode *KDNode::getRight()
{

    return right;
}
void KDNode::setParent(KDNode *parent)
{

    this->parent = parent;
}
KDNode *KDNode::getParent()
{

    return parent;
}
void KDNode::setIndices(vector<int> indices)
{

    this->indices = indices;
}

vector<int> KDNode::getIndices()
{
    return indices;
}

// Get median of a vector of doubles in O(n) time
double GetMedian(vector<double> &values)
{
    nth_element(values.begin(), values.begin() + values.size() / 2, values.end());
    return values[values.size() / 2];
}

KDNode *KDTreeIndex::searchnode(KDNode *node, DataVector &dv)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->isLeaf())
    {
        return node;
    }
    int axis = node->getAxis();
    if (dv[axis] < node->getMedian())
    {
        return searchnode(node->getLeft(), dv);
    }
    else
    {
        return searchnode(node->getRight(), dv);
    }
}

double KDTreeIndex::ChooseRule(vector<int> &indices, int axis)
{
    vector<double> values;
    for (int i = 0; i < indices.size(); i++)
    {
        values.push_back(dataset[indices[i]][axis]);
    }
    return GetMedian(values);
}
KDNode *KDTreeIndex::BuildKDTree(vector<int> &indices, int depth)
{
    int flag = 0;
    KDNode *node = new KDNode();
    int axis = depth % dataset[0].size();
    node->setAxis(axis);
    if (indices.size() == 0)
    {
        node->setLeaf(true);
        return node;
    }
    if (indices.size() <= MINIMUM_SIZE)
    {
        node->setLeaf(true);
        node->setIndices(indices);
        return node;
    }

    double median = ChooseRule(indices, axis);
    node->setMedian(median);
    vector<int> leftIndices, rightIndices;
    for (int i = 0; i < indices.size(); i++)
    {
        if (dataset[indices[i]][axis] < median)
        {
            leftIndices.push_back(indices[i]);
        }
        else
        {
            rightIndices.push_back(indices[i]);
        }
    }
    // prevent infinite recursion
    if (leftIndices.size() == indices.size() || rightIndices.size() == indices.size())
    //     flag = 1, no_change_count++;
    // else
    //     no_change_count = 0;
    // if (no_change_count > 10)
    {
        no_change_count--;
        node->setLeaf(true);
        node->setIndices(indices);
        return node;
    }
    node->setLeft(BuildKDTree(leftIndices, depth + 1));
    // if (flag)
    //     no_change_count--;
    node->setRight(BuildKDTree(rightIndices, depth + 1));
    node->getLeft()->setParent(node);
    node->getRight()->setParent(node);
    return node;
}
void KDTreeIndex::BuildKDTree()
{
    vector<int> indices;
    for (int i = 0; i < dataset.size(); i++)
    {
        indices.push_back(i);
    }
    root = BuildKDTree(indices, 0);
}
void KDTreeIndex::ReadData(const char *filename, int n, int d)
{
    TreeIndex::ReadData(filename, n, d);
}
void KDTreeIndex::PrintData()
{
    dataset.PrintDataset();
}
void KDTreeIndex::PrintKDTree(KDNode *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->isLeaf())
    {
        vector<int> indices = node->getIndices();
        for (int i = 0; i < indices.size(); i++)
        {
            cout << indices[i] << " ";
        }
        cout << endl;
        return;
    }
    cout << "Axis: " << node->getAxis() << " Median: " << node->getMedian() << endl;
    PrintKDTree(node->getLeft());
    PrintKDTree(node->getRight());
}
void KDTreeIndex::PrintKDTree()
{
    PrintKDTree(root);
}
void KDTreeIndex::KDAddDataVector(DataVector &dv)
{
    dataset.AddDataVector(dv);
    KDNode *node = searchnode(root, dv);
    if (node == NULL)
    {
        cerr << "Error: could not find node" << endl;
        exit(1);
    }
    vector<int> indices = node->getIndices();
    indices.push_back(dataset.size() - 1);

    if (indices.size() <= MINIMUM_SIZE)
    {
        node->setIndices(indices);
        return;
    }
    node->setLeaf(false);
    int axis = node->getAxis();
    if (node->getParent() == NULL)
    {
        root = BuildKDTree(indices, 0);
        return;
    }
    KDNode *parent = node->getParent();
    KDNode *newNode = BuildKDTree(indices, axis);
    newNode->setParent(parent);
    if (parent->getLeft() == node)
    {
        parent->setLeft(newNode);
    }
    else
    {
        parent->setRight(newNode);
    }
    free(node);
}
void KDTreeIndex::KDDeleteDataVector(DataVector &dv)
{
    dataset.DeleteDataVector(dv);
    KDNode *node = searchnode(root, dv);
    if (node == NULL)
    {
        cerr << "Error: could not find node" << endl;
        exit(1);
    }
    vector<int> indices = node->getIndices();
    for (int i = 0; i < indices.size(); i++)
    {
        if (dataset[indices[i]] == dv)
        {
            indices.erase(indices.begin() + i);
            break;
        }
    }
    node->setIndices(indices);
}
vector<DataVector> KDTreeIndex::getDataVectors(vector<int> indices)
{
    vector<DataVector> result;
    for (int i = 0; i < indices.size(); i++)
    {
        result.push_back(dataset[indices[i]]);
    }
    return result;
}
// A recursive backtracking function to find the k nearest neighbors
// goes to the leaf node that contains the query point
// backtracks to the parent node and checks the other child node if necessary
KDNode *KDTreeIndex::searchKNN(KDNode *node, DataVector &query, int k, priority_queue<pair<double, int>> &neighbors, int &count)
{
    count++;
    if (node == NULL)
    {
        return NULL;
    }

    int axis = node->getAxis();

    // Handle leaves (store data) and non-leaves (null data) separately
    if (node->isLeaf())
    {
        for (auto index : node->getIndices())
        {
            double dist = query.distance(dataset[index]); // Access data for leaf nodes
            if (neighbors.size() < k || dist < neighbors.top().first)
            {
                neighbors.push({dist, index});
                if (neighbors.size() > k)
                {
                    neighbors.pop(); // Keep only k closest neighbors
                }
            }
        }
    }
    else
    {
        // Calculate a hypothetical distance for non-leaf nodes using median
        double dist = abs(query[axis] - node->getMedian());
        if (neighbors.size() < k || dist < neighbors.top().first)
        {
            // Potentially explore both subtrees
            if (query[axis] < node->getMedian())
            {
                searchKNN(node->getLeft(), query, k, neighbors, count);
                searchKNN(node->getRight(), query, k, neighbors, count);
            }
            else
            {
                searchKNN(node->getRight(), query, k, neighbors, count);
                searchKNN(node->getLeft(), query, k, neighbors, count);
            }
        }
    }

    return NULL; // No further node to explore
}

vector<pair<double, int>> KDTreeIndex::knnSearch(DataVector &query, int k)
{
    int count = 0;
    priority_queue<pair<double, int>> neighbors; // Max-heap for nearest neighbors
    searchKNN(root, query, k, neighbors, count);

    // cout << '\n'
    //      << count << '\n';
    vector<pair<double, int>> results;
    while (!neighbors.empty())
    {
        results.push_back(neighbors.top());
        neighbors.pop();
    }
    reverse(results.begin(), results.end()); // Reverse for ascending order
    return results;
}

void RPNode::setLeaf(bool leaf)
{
    this->leaf = leaf;
}
bool RPNode::isLeaf()
{
    return leaf;
}
void RPNode::setAxis(DataVector axis)
{
    this->axis = axis;
}
DataVector RPNode::getAxis()
{
    return axis;
}
void RPNode::setThreshold(double threshold)
{
    this->threshold = threshold;
}
double RPNode::getThreshold()
{
    return threshold;
}
void RPNode::setLeft(RPNode *left)
{
    this->left = left;
}
RPNode *RPNode::getLeft()
{
    return left;
}
void RPNode::setRight(RPNode *right)
{
    this->right = right;
}
RPNode *RPNode::getRight()
{
    return right;
}
void RPNode::setParent(RPNode *parent)
{
    this->parent = parent;
}
RPNode *RPNode::getParent()
{
    return parent;
}
void RPNode::setIndices(vector<int> indices)
{
    this->indices = indices;
}
vector<int> RPNode::getIndices()
{
    return indices;
}

RPNode *RPTreeIndex::searchnode(RPNode *node, DataVector &dv)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (node->isLeaf())
    {
        return node;
    }
    DataVector axis = node->getAxis();
    double dot = dv * axis;
    if (dot < node->getThreshold())
    {
        return searchnode(node->getLeft(), dv);
    }
    else
    {
        return searchnode(node->getRight(), dv);
    }
}

double RPTreeIndex::ChooseRule(vector<int> &indices, DataVector &axis)
{
    vector<double> values;
    for (int i = 0; i < indices.size(); i++)
    {
        values.push_back(dataset[indices[i]] * axis);
    }
    return GetMedian(values);
}
RPNode *RPTreeIndex::BuildRPTree(vector<int> &indices, int depth)
{
    srand(time(NULL));
    int flag = 0;
    RPNode *node = new RPNode();

    DataVector axis;
    axis.setDimension(dataset[0].size());
    for (int i = 0; i < axis.size(); i++)
        axis[i] = (double)(rand() % 1000);
    int norm = axis.norm();
    for (int i = 0; i < axis.size(); i++)
        axis[i] /= norm;
    node->setAxis(axis);

    if (indices.size() == 0)
    {
        node->setLeaf(true);
        return node;
    }
    if (indices.size() <= MINIMUM_SIZE)
    {
        node->setLeaf(true);
        node->setIndices(indices);
        return node;
    }

    double threshold = ChooseRule(indices, axis);

    int idx = rand() % indices.size();
    DataVector dv = dataset[indices[idx]];
    double farthest = 0;
    for (int i = 0; i < indices.size(); i++)
    {
        double dist = dv.distance(dataset[indices[i]]);
        if (dist > farthest)
            farthest = dist;
    }
    double random_double = (double)rand() / (RAND_MAX) * 2.0 - 1;
    double delta = random_double * farthest / sqrt(dv.size()) * 0.06;
    threshold += delta;
    node->setThreshold(threshold);

    vector<int> leftIndices, rightIndices;
    for (int i = 0; i < indices.size(); i++)
    {
        if (dataset[indices[i]] * axis < threshold)
        {
            leftIndices.push_back(indices[i]);
        }
        else
        {
            rightIndices.push_back(indices[i]);
        }
    }
    // prevent infinite recursion
    if (leftIndices.size() == indices.size() || rightIndices.size() == indices.size())
    //     flag = 1, no_change_count++;
    // else
    //     no_change_count = 0;
    // if (no_change_count > 10)
    {
        no_change_count--;
        node->setLeaf(true);
        node->setIndices(indices);
        return node;
    }
    node->setLeft(BuildRPTree(leftIndices, depth + 1));
    // if (flag)
    //     no_change_count--;
    node->setRight(BuildRPTree(rightIndices, depth + 1));
    node->getLeft()->setParent(node);
    node->getRight()->setParent(node);
    return node;
}
void RPTreeIndex::BuildRPTree()
{
    vector<int> indices;
    for (int i = 0; i < dataset.size(); i++)
    {
        indices.push_back(i);
    }
    root = BuildRPTree(indices, 0);
}
void RPTreeIndex::ReadData(const char *filename, int n, int d)
{
    TreeIndex::ReadData(filename, n, d);
}
void RPTreeIndex::PrintData()
{
    dataset.PrintDataset();
}
void RPTreeIndex::PrintRPTree(RPNode *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->isLeaf())
    {
        vector<int> indices = node->getIndices();
        for (int i = 0; i < indices.size(); i++)
        {
            cout << indices[i] << " ";
        }
        cout << endl;
        return;
    }
    cout << "Axis: ";
    for (int i = 0; i < node->getAxis().size(); i++)
    {
        cout << node->getAxis()[i] << " ";
    }
    cout << "Threshold: " << node->getThreshold() << endl;
    PrintRPTree(node->getLeft());
    PrintRPTree(node->getRight());
}
void RPTreeIndex::PrintRPTree()
{
    PrintRPTree(root);
}
void RPTreeIndex::RPAddDataVector(DataVector &dv)
{
    dataset.AddDataVector(dv);
    RPNode *node = searchnode(root, dv);
    if (node == NULL)
    {
        cerr << "Error: could not find node" << endl;
        exit(1);
    }
    vector<int> indices = node->getIndices();
    indices.push_back(dataset.size() - 1);

    if (indices.size() <= MINIMUM_SIZE)
    {
        node->setIndices(indices);
        return;
    }
    node->setLeaf(false);
    DataVector axis = node->getAxis();
    if (node->getParent() == NULL)
    {
        root = BuildRPTree(indices, 0);
        return;
    }
    RPNode *parent = node->getParent();
    if (parent == NULL)
    {
        root = BuildRPTree(indices, 0);
        return;
    }
    RPNode *newNode = BuildRPTree(indices, 0);
    newNode->setParent(parent);
    if (parent->getLeft() == node)
    {
        parent->setLeft(newNode);
    }
    else
    {
        parent->setRight(newNode);
    }
    free(node);
}
void RPTreeIndex::RPDeleteDataVector(DataVector &dv)
{
    dataset.DeleteDataVector(dv);
    RPNode *node = searchnode(root, dv);
    if (node == NULL)
    {
        cerr << "Error: could not find node" << endl;
        exit(1);
    }
    vector<int> indices = node->getIndices();
    for (int i = 0; i < indices.size(); i++)
    {
        if (dataset[indices[i]] == dv)
        {
            indices.erase(indices.begin() + i);
            break;
        }
    }
    node->setIndices(indices);
}
vector<DataVector> RPTreeIndex::getDataVectors(vector<int> indices)
{
    vector<DataVector> result;
    for (int i = 0; i < indices.size(); i++)
    {
        result.push_back(dataset[indices[i]]);
    }
    return result;
}
// A recursive backtracking function to find the k nearest neighbors
// goes to the leaf node that contains the query point
// backtracks to the parent node and checks the other child node if necessary
RPNode *RPTreeIndex::searchKNN(RPNode *node, DataVector &query, int k, priority_queue<pair<double, int>> &neighbors, int &count)
{
    count++;
    if (node == NULL)
    {
        return NULL;
    }

    // Handle leaves (store data) and non-leaves (null data) separately
    if (node->isLeaf())
    {
        for (auto index : node->getIndices())
        {
            double dist = query.distance(dataset[index]); // Access data for leaf nodes
            if (neighbors.size() < k || dist < neighbors.top().first)
            {
                neighbors.push({dist, index});
                if (neighbors.size() > k)
                {
                    neighbors.pop(); // Keep only k closest neighbors
                }
            }
        }
    }
    else
    {
        // Calculate a hypothetical distance for non-leaf nodes using axis and threshold
        double dist = abs(query * node->getAxis() - node->getThreshold());
        if (neighbors.size() < k || dist < neighbors.top().first)
        {
            // Potentially explore both subtrees
            if (query * node->getAxis() < node->getThreshold())
            {
                searchKNN(node->getLeft(), query, k, neighbors, count);
                searchKNN(node->getRight(), query, k, neighbors, count);
            }
            else
            {
                searchKNN(node->getRight(), query, k, neighbors, count);
                searchKNN(node->getLeft(), query, k, neighbors, count);
            }
        }
    }

    return NULL; // No further node to explore
}
vector<pair<double, int>> RPTreeIndex::knnSearch(DataVector &query, int k)
{
    int count = 0;
    priority_queue<pair<double, int>> neighbors; // Max-heap for nearest neighbors
    searchKNN(root, query, k, neighbors, count);
    // cout << '\n'
    //      << count << '\n';

    vector<pair<double, int>> results;
    while (!neighbors.empty())
    {
        results.push_back(neighbors.top());
        neighbors.pop();
    }
    reverse(results.begin(), results.end()); // Reverse for ascending order
    return results;
}

int main()
{
    cout << "Welcome to TreeIndex\n";

    bool chooseTree;
    cout << "Choose tree: 0 for KDTree, 1 for RPTree: ";
    cin >> chooseTree;

    const char *trainset = "trainset.csv";

    int testsize = 6000000;
    int dimension = 5;

    if (chooseTree)
    {
        auto begin = chrono::high_resolution_clock::now();
        RPTreeIndex::GetInstance().ReadData(trainset, testsize, dimension);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

        begin = chrono::high_resolution_clock::now();
        RPTreeIndex::GetInstance().BuildRPTree();
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

        begin = chrono::high_resolution_clock::now();
        DataVector query(dimension);
        for (int i = 0; i < dimension; i++)
        {
            query[i] = 0;
        }
        vector<pair<double, int>> result = RPTreeIndex::GetInstance().knnSearch(query, 5);
        for (int i = 0; i < result.size(); i++)
        {
            cout << "Distance: " << result[i].first << ", Index: " << result[i].second << endl;
        }
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    }
    else
    {
        auto begin = chrono::high_resolution_clock::now();
        KDTreeIndex::GetInstance().ReadData(trainset, testsize, dimension);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

        begin = chrono::high_resolution_clock::now();
        KDTreeIndex::GetInstance().BuildKDTree();
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

        begin = chrono::high_resolution_clock::now();
        DataVector query(dimension);
        for (int i = 0; i < dimension; i++)
        {
            query[i] = 0;
        }
        vector<pair<double, int>> result = KDTreeIndex::GetInstance().knnSearch(query, 5);
        for (int i = 0; i < result.size(); i++)
        {
            cout << "Distance: " << result[i].first << ", Index: " << result[i].second << endl;
        }
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";
    }
    return 0;
}