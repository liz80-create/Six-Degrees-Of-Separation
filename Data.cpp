#include "Data.h"
// from class DataReader
using namespace std;
unordered_map<int, string> DataReader::readPeopleData(const string &filename)
{
    unordered_map<int, string> people;
    ifstream peopleFile(filename);
    if (!peopleFile.is_open())
    {
        throw runtime_error("Unable to open people CSV file.");
    }
    string line;
    while (getline(peopleFile, line))
    {
        istringstream iss(line);
        string field;
        vector<string> fields;
        while (getline(iss, field, ','))
        {
            fields.push_back(field);
        }
        if (fields.size() < 3)
        {
            continue;
        }
        int personId;
        try
        {
            personId = stoi(fields[0]);
        }
        catch (const std::invalid_argument &e)
        {
            continue;
        }
        string displayName = fields[2];
        people[personId] = displayName;
    }
    peopleFile.close();
    return people;
}

vector<vector<int>> DataReader::readRelationshipsData(const string &filename)
{
    vector<vector<int>> graph;
    ifstream relationshipsFile(filename);
    if (!relationshipsFile.is_open())
    {
        throw runtime_error("Unable to open relationships CSV file.");
    }
    string line;
    getline(relationshipsFile, line); // Skip header
    while (getline(relationshipsFile, line))
    {
        istringstream iss(line);
        string field;
        vector<string> fields;
        while (getline(iss, field, ','))
        {
            fields.push_back(field);
        }
        int person1Id = stoi(fields[1]);
        int person2Id = stoi(fields[2]);
        int maxSize = max(person1Id, person2Id) + 1;
        if (graph.size() < maxSize)
        {
            graph.resize(maxSize);
        }
        graph[person1Id].push_back(person2Id);
        graph[person2Id].push_back(person1Id);
    }
    relationshipsFile.close();
    return graph;
}

// from class
pair<int, vector<int>> DegreeFinder::findDegreeOfSeparation(const vector<vector<int>> &graph, int start, int end)
{
    if (start == end)
    {
        return make_pair(0, vector<int>{start});
    }

    unordered_set<int> visitedStart, visitedEnd;
    queue<int> qStart, qEnd;
    unordered_map<int, int> parentStart, parentEnd;
    qStart.push(start);
    qEnd.push(end);
    visitedStart.insert(start);
    visitedEnd.insert(end);

    while (!qStart.empty() && !qEnd.empty())
    {
        int levelSizeStart = qStart.size();
        for (int i = 0; i < levelSizeStart; i++)
        {
            int current = qStart.front();
            qStart.pop();
            if (visitedEnd.find(current) != visitedEnd.end())
            {
                return reconstructPath(parentStart, parentEnd, start, end, current);
            }
            for (int neighbor : graph[current])
            {
                if (visitedStart.find(neighbor) == visitedStart.end())
                {
                    qStart.push(neighbor);
                    visitedStart.insert(neighbor);
                    parentStart[neighbor] = current;
                }
            }
        }
        int levelSizeEnd = qEnd.size();
        for (int i = 0; i < levelSizeEnd; i++)
        {
            int current = qEnd.front();
            qEnd.pop();
            if (visitedStart.find(current) != visitedStart.end())
            {
                return reconstructPath(parentStart, parentEnd, start, end, current);
            }
            for (int neighbor : graph[current])
            {
                if (visitedEnd.find(neighbor) == visitedEnd.end())
                {
                    qEnd.push(neighbor);
                    visitedEnd.insert(neighbor);
                    parentEnd[neighbor] = current;
                }
            }
        }
        degree++;
    }
    return make_pair(-1, vector<int>());
}

pair<int, vector<int>> DegreeFinder::reconstructPath(unordered_map<int, int> &sourceParent, unordered_map<int, int> &targetParent,
                                                     int source, int target, int current)
{
        vector<int> path;
        int node = current;
        while (node != source)
        {
            path.push_back(node);
            node = sourceParent[node];
        }
        path.push_back(source);
        reverse(path.begin(), path.end());
        node = current;
        while (node != target)
        {
            node = targetParent[node];
            path.push_back(node);
        }
        return make_pair(degree + 1, path);

        /*
                logic for above : (same for both traversal)
                if start=1 and end=6  ,node =4
                parentStart      parentEnd            
                    4->1            4->6
                while(4!=start i.e 1)
                   push 4 in path
                   push parent of 4 i.e 1 in path
                   path: 4->1
                reverse the path - 1-> 4

                while(4 != end i.e 6)
                {
                    push parent of 4 i.e 6 in path
                    path - 1->4->6
                }
                return degree and path
            */
}
