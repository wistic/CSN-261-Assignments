/**
 * @file main.cpp
 * @author Prathamesh
 * @brief Main file for L3
 * @version 0.1
 * @date 2019-10-02
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "FibonacciHeap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <sstream>
#include <vector>

using namespace std;

/**
 * @brief Class to store vertex and key pair
 *
 */
class VertexKey
{
public:
    int index;
    int key;

    VertexKey(int index, int key) : index(index), key(key) {}

    bool operator<(const VertexKey &other)
    {
        return (key < other.key);
    }
};

/**
 * @brief Reads the file and convert to collecions of edges
 *
 * @param name Name of the file
 * @return vector<tuple<string, string, int>>
 */
vector<tuple<string, string, int>> readFile(std::string name)
{
    std::fstream file;
    file.open(name);
    if (!file)
        return vector<tuple<string, string, int>>();
    vector<tuple<string, string, int>> result;
    std::string line;
    while (getline(file, line))
    {
        std::stringstream stream(line);
        std::string a, b;
        int weight;
        getline(stream, a, ',');
        getline(stream, b, ',');
        stream >> weight;
        result.push_back({a, b, weight});
    }
    file.close();
    return result;
}

/**
 * @brief Find the vertex from collection of Strings
 *
 * @param vertices Strings
 * @param name string to find
 * @return optional<int>
 */
optional<int> findVertex(vector<string> &vertices, string name)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (name == vertices[i])
            return {i};
    }
    return {};
}

/**
 * @brief Generates the collection of vertices from file Contents
 *
 * @param fileEdges FileEdges to use
 * @return vector<string>
 */
vector<string> generateVertices(vector<tuple<string, string, int>> &fileEdges)
{
    vector<string> result;
    for (auto tup : fileEdges)
    {
        if (!findVertex(result, get<0>(tup)))
            result.push_back(get<0>(tup));
        if (!findVertex(result, get<1>(tup)))
            result.push_back(get<1>(tup));
    }
    return result;
}

/**
 * @brief Print edges to console
 *
 * @param edges Edges to use
 * @param relation Relation to use
 * @param vertices Vertices to use
 */
void printEdges(vector<vector<VertexKey>> &edges, unique_ptr<int[]> &relation, vector<string> &vertices)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (relation[i] != i && relation[i] != -1)
        {
            int weight = 0;
            for (auto j : edges[i])
            {
                if (j.index == relation[i])
                    weight = j.key;
            }
            cout << vertices[i] << " " << vertices[relation[i]] << " " << weight << endl;
        }
    }
}

/**
 * @brief Recursively prints to file
 *
 * @param vertex Currently used vertex
 * @param file File stream to use
 * @param relation Relation of parent
 * @param vertices Vertices to use
 * @param graph Edge Data to use
 */
void printNewick(int vertex, ostream &file, unique_ptr<int[]> &relation, vector<string> &vertices,
                 vector<vector<VertexKey>> &graph)
{
    int childCount = 0;
    for (int i = 0; i < vertices.size(); i++)
    {
        if (relation[i] == vertex)
            childCount++;
    }
    if (childCount > 0)
    {
        file << '(';
        for (int i = 0; i < vertices.size(); i++)
        {

            if (relation[i] == vertex)
            {
                printNewick(i, file, relation, vertices, graph);
                if (childCount > 1)
                {
                    childCount--;
                    file << ',';
                }
            }
        }
        file << ')';
    }
    file << vertices[vertex];

    int weight = 0;
    for (auto j : graph[vertex])
    {
        if (j.index == relation[vertex])
            weight = j.key;
    }
    file << ":" << weight << ".0";
}

/**
 * @brief Generates the edge data for graph
 *
 * @param fileEdges FileEdges to use
 * @param vertices vertices to use
 * @return vector<vector<VertexKey>>
 */
vector<vector<VertexKey>>
generateAdjacentVertices(vector<tuple<string, string, int>> &fileEdges, vector<string> &vertices)
{
    vector<vector<VertexKey>> result(vertices.size());
    for (auto tup : fileEdges)
    {
        auto va = findVertex(vertices, get<0>(tup));
        auto vb = findVertex(vertices, get<1>(tup));
        if (va && vb)
        {
            int weight = get<2>(tup);
            result[*va].push_back(VertexKey(*vb, weight));
            result[*vb].push_back(VertexKey(*va, weight));
        }
    }
    return result;
}

/**
 * @brief Main function to use
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "wrong arguments";
        return EXIT_FAILURE;
    }
    auto fileEdges = readFile(argv[1]);
    auto vertices = generateVertices(fileEdges);
    auto adjacentVetices = generateAdjacentVertices(fileEdges, vertices);
    Heap<VertexKey> heap;
    unique_ptr<int[]> key = make_unique<int[]>(vertices.size());
    unique_ptr<int[]> relation = make_unique<int[]>(vertices.size());
    unique_ptr<int[]> included = make_unique<int[]>(vertices.size());

    for (int i = 0; i < vertices.size(); i++)
    {
        key[i] = (~1u >> 1);
        relation[i] = -1;
        included[i] = false;
    }

    int source = 0;
    heap.insert(VertexKey(source, 0));
    key[source] = 0;
    while (!heap.empty())
    {
        VertexKey vertex = *heap.extract();
        included[vertex.index] = true;
        for (auto adjacent : adjacentVetices[vertex.index])
        {
            if (!included[adjacent.index] && key[adjacent.index] > adjacent.key)
            {
                key[adjacent.index] = adjacent.key;
                heap.insert(VertexKey(adjacent.index, key[adjacent.index]));
                relation[adjacent.index] = vertex.index;
            }
        }
    }
    printEdges(adjacentVetices, relation, vertices);

    ofstream file;
    file.open(argv[2]);
    if (!file)
    {
        cout << "cant open file";
        return -1;
    }
    printNewick(0, file, relation, vertices, adjacentVetices);
    file << ';';
    file.close();
    return 0;
}