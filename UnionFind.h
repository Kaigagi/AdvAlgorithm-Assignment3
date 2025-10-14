#pragma once
#include <vector>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

class UnionFind
{
public:
    vector<int> parentList;
    vector<int> rankList;

    UnionFind(int size);
    ~UnionFind() {}

    int Find(int i);

    bool Union(int i, int j);
};


