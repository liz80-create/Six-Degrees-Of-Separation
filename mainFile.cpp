#include "Data.h"
#include <cstdlib> // for atoi

using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <start_person_ID> <end_person_ID>" << endl;
        return 1;
    }

    string person1 = argv[1];
    string person2 = argv[2];

    DataReader reader;
    DegreeFinder finder;

    try
    {
        unordered_map<int, string> people = reader.readPeopleData("SDFB_people.csv");
        vector<vector<int>> graph = reader.readRelationshipsData("SDFB_relationships_100000000_100020000.csv");
        // Find IDs in the map
        int start = -1; // Default value if person not found
        int end = -1;   // Default value if person not found
        for (const auto &pair : people)
        {
            if (pair.second == person1)
            {
                start = pair.first;
            }
            if (pair.second == person2)
            {
                end = pair.first;
            }
        }
        // Check if names exist in the map
        if (start == -1 || end == -1)
        {
            cout <<"Person names not found in the map.\n";
            return 1;
        }
        pair<int, vector<int>> result = finder.findDegreeOfSeparation(graph, start, end);
        int degree = result.first;
        vector<int> path = result.second;

        if (degree == -1)
        {
            cout << "No path found between the start and end persons." << endl;
        }
        else
        {
            cout << "\nPath: ";
            for (int i = 0; i < path.size(); ++i)
            {
                cout << people[path[i]] << " (ID: " << path[i] << ")";
                if (i != path.size() - 1)
                {
                    cout << " -> ";
                    // Insert newline after every 4 names
                    if ((i + 1) % 3 == 0)
                    {
                        cout << "\n";
                    }
                }
            }
            cout << endl;

            cout << "\nThe degree of separation between " << people[start] << " (ID: " << start << ") and "
                 << people[end] << " (ID: " << end << ") is: " << degree << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}
