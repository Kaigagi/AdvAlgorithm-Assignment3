#include "UnionFind.h"

UnionFind::UnionFind(int size)
{
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative.");
    }

    // Initialize parentList: every element is its own root
    parentList.resize(size);
    std::iota(parentList.begin(), parentList.end(), 0); // Fills with 0, 1, 2, ... size-1

    // Initialize rankList: all ranks are 0 initially
    rankList.resize(size, 0);
}

int UnionFind::Find(int i)
{
    // Basic validation
    if (i < 0 || i >= parentList.size()) {
        throw std::out_of_range("Element index out of bounds in Find.");
    }

    // Base case: 'i' is the root of its set
    if (parentList[i] == i) {
        return i;
    }

    //flatten the tree whenever the vertex is not the root
    parentList[i] = Find(parentList[i]);
    return parentList[i];
}

bool UnionFind::Union(int i, int j)
{
    // Basic validation
    if (i < 0 || i >= parentList.size() || j < 0 || j >= parentList.size()) {
        throw std::out_of_range("Element index out of bounds in Union.");
    }

    int root_i = Find(i);
    int root_j = Find(j);

    // If both elements already have the same root, they are already in the same set.
    if (root_i == root_j) {
        return false; // No union performed
    }

    // Union by Rank: attach the tree with the smaller rank to the root of the tree with the larger rank.
    if (rankList[root_i] < rankList[root_j]) {
        parentList[root_i] = root_j;
    } else if (rankList[root_i] > rankList[root_j]) {
        parentList[root_j] = root_i;
    } else {
        // Ranks are equal: pick one as the new root (e.g., root_i) and increment its rank.
        parentList[root_j] = root_i;
        rankList[root_i]++;
    }

    return true;
}

void UnionFind::Print() const
{
    std::cout << "Union-Find Structure:\n";

    for (int i = 0; i < parentList.size(); ++i)
    {
        // Find root without modifying structure (const)
        int root = i;
        while (root != parentList[root])
            root = parentList[root];

        std::cout << "Element " << i
                  << " | Parent = " << parentList[i]
                  << " | Root = " << root
                  << " | Rank = " << rankList[i]
                  << "\n";
    }

    std::cout << std::endl;
}