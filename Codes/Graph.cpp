#include <bits/stdc++.h>

using namespace std;

// Graph class to store the database
class Graph 
{
    public:
    unordered_map<string, vector<pair<string,double>>> adjacencyList;

    void addEdge(string source, string destination, double preference) 
    {      
        adjacencyList[source].push_back({destination,preference});
    }

    bool checkEdge(string source, string destination)
    {
        if(adjacencyList.count(source)==1)
        {
            for(auto neighbor : adjacencyList[source])
            {
                if(neighbor.first==destination) return 1;
            }
        }
        return 0;
    }
    
    vector<pair<string,double>> getCourses(string prof)
    {
        return adjacencyList[prof];
    }

    bool equalTo(Graph g)
    {
        for(auto i : g.adjacencyList)
        {
            if(i.second.size()>0)
            {for(auto j : i.second)
            {
                if(!checkEdge(i.first, j.first))
                {
                    return 0;
                }
            }}
        }
        for(auto i : adjacencyList)
        {
            if(i.second.size()>0)
            {for(auto j : i.second)
            {
                if(!g.checkEdge(i.first, j.first))
                {
                    return 0;
                }
            }}
        }
        return 1;
    }
    // Display the graph
    void displayGraph() 
    {
        for (auto entry : adjacencyList) 
        {
            if(entry.second.size()>0)
            {
                cout << entry.first<< " : ";
                for (auto neighbor : entry.second) 
                {
                    if(neighbor.first!=(*(--entry.second.end())).first)
                    cout <<"(" << neighbor.first<< ", "<< neighbor.second <<"), ";
                    else
                    cout <<"(" << neighbor.first<< ", "<< neighbor.second <<")";
                }
                cout << endl;
            }
        }
    }
};