
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

class AdjacencyList{
private:
    //Basic adjency list with from, being string, and the vector being all the vertex the key points to.
    map<string , vector<string>> graph;
    // Map where it structured where key is "to", and all the vertexes that point to it are in the vector.
    map<string, vector<string>> outDegree;
    // Main rank map used to print
    map<string, float> rank;
    // Other map to store the newly updated rank.
    map<string, float> update;

public:
    //Insert function inspired by programming quiz graphs 1, and adjacency list code from slides.
    void insertEdge(string from, string to)
    {
        graph[to].push_back(from);
        outDegree[from].push_back(to);

        if (graph.find(from)==graph.end())
        {
            graph[from] = {};
        }
        if (outDegree.find(to) == outDegree.end())
        {
            outDegree[to] = {};
        }

    }

    void PageRank(int n)
    {
        // Initialize my rank with default rank of 1/|v|, and update map for later with zeros.
        initializeMaps();

        // Starts at one since, if p = 1, and its the default ranks.
        auto i = 1;
        while (i < n)
        {
            // Goes through every vertex.
            for (auto it = graph.begin(); it != graph.end() ; it++)
            {
                float sum = 0;
                //Goes through the vector inside at iterator.
                for (int i = 0 ; i < it->second.size(); i++)
                {
                    // Calculates the new rank by with (1/outdegree j) * (rank of i)
                    sum = sum + (1.0f / outDegree.find(it->second.at(i))->second.size()) * (rank[it->second.at(i)]);
                }
                //put the new rank into the update map.
                update[it->first] = sum;
                sum = 0;
            }
            //Goes to updaterank function that puts the new rank in update, into the main map named rank.
            rank = update;
            i++;
        }

        // Prints out ranks once we reach the required number of power iterations.
        for (auto it = rank.begin(); it != rank.end(); it++)
        {
            cout << setprecision(2) << fixed << it->first << " " << it->second << endl;
        }

    }
    
    // Puts in the default values into the rank and update map.
    void initializeMaps()
    {
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            rank[it->first] = 1.0f / graph.size();
        }

        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            update[it->first] = 0.0f;
        }
    }

    // Test function, to understand what graph is holding.
    void graphprinttest()
    {
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            cout << it->first << endl;
            for (int i = 0; i < it->second.size() ; i++)
            {
                cout << it->second.at(i) << " ";
            }
            cout << "next" << endl;

        }
    }

    // To see if every vertex has proper out degree.
    void outdegreeprinttest()
    {
        for (auto it = outDegree.begin() ; it != outDegree.end(); it++)
        {
            cout << it->first << " " << it->second.size() << endl;
        }
    }

    // Checks to see if ranks are right.
    void printRank()
    {
        for (auto it = rank.begin() ; it != rank.end(); it++)
        {
            cout << it->first << " " <<it->second << endl;
        }
    }

};

int main()
{
    AdjacencyList web;
    int no_of_lines, power_itations;
    std::string from, to;
    std::cin >> no_of_lines;
    std::cin >> power_itations;
    for(int i = 0; i < no_of_lines; i++)
    {
        std::cin >> from;
        std::cin >> to;
        web.insertEdge(from, to);
    }
    web.PageRank(power_itations);
}

