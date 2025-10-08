#include <vector>

using namespace std;

class UnionFind
{
public:
    vector<int> parentList;
    void AddToTree(int index, int target);
    UnionFind(int size);
    ~UnionFind();
};


