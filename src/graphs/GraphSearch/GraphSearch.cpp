#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include "../include/Graph.h"
#include "../include/Edge.h"
#include "../include/Vertex.h"
#include "../include/SparseGraph.h"
#include "../include/Dfs.h"
#include "../include/Bfs.h"
using namespace std;

Graph& Graph::getGraph(bool isDirected)
{
    Graph *pGraph = new SparseGraph(isDirected);
    return *pGraph;
}

vector<size_t> WalkTree(const shared_ptr<SearchUndirected>& search, 
    shared_ptr<Vertex> v,
    unordered_set<size_t>& visitedVertices)
{
    if (!v) { return {}; }

    vector<size_t> ancestors;

    ancestors.push_back(v->getId());
    visitedVertices.insert(v->getId());
    
    while (true)
    {
        const auto& parent = search->Parent(v);
        if (v->getId() == parent->getId())
        {
            break;
        }
        ancestors.push_back(parent->getId());
        visitedVertices.insert(parent->getId());
        v = parent;
    }
    return ancestors;
}

int main()
{
    Graph& graph = Graph::getGraph(false);

    vector<shared_ptr<Vertex>> vertices;
    for (auto i = 0; i < 10; ++i) { vertices.emplace_back(make_shared<Vertex>("")); }
    
    vector<shared_ptr<Edge>> edges = 
    {
        make_shared<Edge>(vertices[0], vertices[2]),
        make_shared<Edge>(vertices[0], vertices[5]),
        make_shared<Edge>(vertices[0], vertices[7]),
        make_shared<Edge>(vertices[1], vertices[7]),
        make_shared<Edge>(vertices[2], vertices[6]),
        make_shared<Edge>(vertices[3], vertices[4]),
        make_shared<Edge>(vertices[3], vertices[5]),
        make_shared<Edge>(vertices[4], vertices[6]),
        make_shared<Edge>(vertices[4], vertices[7]),
    };

    for (const auto& edge : edges) { graph.Insert(edge); }

    // Print search tree
    
    for (size_t i = 0; i < 2; ++i)
    {
        shared_ptr<SearchUndirected> search;
        if (i == 0)
        {
            search = make_shared<DFS>(graph);
            cout << "DFS Search tree: " << endl;
        }
        else if (i == 1)
        {
            search = make_shared<BFS>(graph);
            cout << "BFS Search tree: " << endl;    
        }

        unordered_set<size_t> visitedVertices;
        auto searchVertices = graph.getVertices();
        for (const auto& it : searchVertices)
        {
            auto id = it->getId();
            if (visitedVertices.find(id) != visitedVertices.cend()) { continue; }

            vector<size_t> ancestors = WalkTree(search, it, visitedVertices);
            for (size_t i = 0; i < ancestors.size(); ++i)
            {
                cout << ancestors[i];
                if (i != ancestors.size() - 1)
                {
                    cout << " -> ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}

