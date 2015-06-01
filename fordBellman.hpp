#include <vector>
#include <utility>
#include <algorithm>

#include "dijkstra.hpp"


template<class Edge>
std::pair<std::vector<typename Edge::PathType>, std::vector<size_t> > fordBellman(size_t startVertex, const Graph<Edge> &graph)
{
    std::vector<typename Edge::PathType> result(graph.getNumberOfVertice(), static_cast<typename Edge::PathType>(Edge::PATH_INFINITY));
    std::vector<size_t> parent(graph.getNumberOfVertice(), static_cast<size_t>(-1));
    
    result[startVertex] = static_cast<typename Edge::PathType>(Edge::PATH_ZERO);
    parent[startVertex] = startVertex;
    
    std::vector<std::pair<size_t, Edge> > edgesList;
    for (size_t vertex = 0; vertex < graph.getNumberOfVertice(); ++vertex)
    {
        for (auto it = graph.constGetEdgeAccess(vertex); it != graph.constGetEdgeAccessEnd(vertex); ++it)
        {
            edgesList.push_back(std::make_pair(vertex, *it));
        }
    }
    
    for (size_t iteration = 0; iteration < graph.getNumberOfVertice(); ++iteration)
    {
        for (auto const &edge: edgesList)
        {
            if (result[edge.first] != static_cast<typename Edge::PathType>(Edge::PATH_INFINITY))
            {
                if (Edge::recalculate(result[edge.first], edge.second) < result[edge.second.getDestination()])
                {
                    result[edge.second.getDestination()] = Edge::recalculate(result[edge.first], edge.second);
                    parent[edge.second.getDestination()] = edge.first;
                }
            }
        }
    }
    return std::make_pair(result, parent);
}