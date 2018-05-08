#pragma once
#include <vector>
#include <unordered_map>
#include "Graph.h"
#include "Edge.h"
#include "Search.h"
#include "Vertex.h"

class SearchDirected : public Search
{
protected:
    size_t count = 0, cCount = 0;
    void SearchGraph(const Graph& graph)
    {
        std::vector<const std::shared_ptr<Vertex>> vertices = graph.getVertices();
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            auto vertexId = vertices[i]->getId();
            if (lookup.find(vertexId) == lookup.cend())
            {
                // add a dummy self edge
                auto dummyVertex = vertices[i];
                std::shared_ptr<Edge> dummyEdge = std::make_shared<Edge>(dummyVertex, dummyVertex);
                SearchComponent(graph, dummyEdge);
                ++cCount;
            }
        }
        SearchInfo::connectedComponentCount = cCount;
    }
    SearchDirected(const Graph& graph) : Search(graph)
    {
        if (!graph.Directed())
        {
            throw std::invalid_argument("this class does not support undirected graphs");
        }
    }
    virtual void SearchComponent(const Graph& graph, const std::shared_ptr<Edge>&) = 0;
};
