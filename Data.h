#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

class DataReader {
public:
    unordered_map<int, string> readPeopleData(const string &filename);
    vector<vector<int>> readRelationshipsData(const string &filename);
};

class DegreeFinder {
public:
    int degree = 0;
    pair<int, vector<int>> findDegreeOfSeparation(const vector<vector<int>> &graph, int start, int end);
private:
    pair<int, vector<int>> reconstructPath(unordered_map<int, int> &sourceParent, unordered_map<int, int> &targetParent,
                                            int source, int target, int current);
};

#endif // DATA_H
