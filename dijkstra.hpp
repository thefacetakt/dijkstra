#ifndef _DIJKSTRA
#define _DIJKSTRA

#include <vector>
#include <utility>
#include <algorithm>
#include <set>

template <class Edge>
class Graph
{
    typedef typename std::vector<Edge>::iterator EdgeIterator;
    typedef typename std::vector<Edge>::const_iterator ConstEdgeIterator;
    
    std::vector <std::vector <Edge> > adjacencyList;
    size_t numberOfVertice;
    
public:
    
    Graph()
    {
    }
    
    Graph(size_t numberOfVertice) : numberOfVertice(numberOfVertice)
    {
        adjacencyList.resize(numberOfVertice);
    }
    
    Graph(std::vector<std::vector<Edge> > &adjacencyList) : adjacencyList(adjacencyList), numberOfVertice(adjacencyList.size())
    {    
    }
    
    void resize(size_t numberOfVertice)
    {
        this->numberOfVertice = numberOfVertice;
        adjacencyList.resize(numberOfVertice);
    }
    
    void addOrientedEdge(size_t source, size_t destination, typename Edge::WeightType weight)
    {
        adjacencyList[source].push_back(Edge(destination, weight));
    }
    
    void addEdge(size_t firstVertex, size_t secondVertex, typename Edge::WeightType weight)
    {
        addOrientedEdge(firstVertex, secondVertex, weight);
        addOrientedEdge(secondVertex, firstVertex, weight);
    }
    
    EdgeIterator getEdgeAccess(size_t vertex)
    {
        return adjacencyList[vertex].begin();
    }
    
    ConstEdgeIterator constGetEdgeAccess(size_t vertex) const
    {
        return adjacencyList[vertex].cbegin();
    }
    
    EdgeIterator getEdgeAccessEnd(size_t vertex)
    {
        return adjacencyList[vertex].end();
    }
    
    ConstEdgeIterator constGetEdgeAccessEnd(size_t vertex) const
    {
        return adjacencyList[vertex].cend();
    }
    
    typename Edge::WeightType getEdgeWeight(ConstEdgeIterator edge) const
    {
        return edge->getWeight();
    }
    
    
    std::pair<std::vector<typename Edge::PathType>, std::vector<size_t> > dijkstra(size_t startVertex)
    {
        std::vector<typename Edge::PathType> distance(numberOfVertice, static_cast<typename Edge::PathType>(Edge::PATH_INFINITY));
        std::vector<size_t> parent(numberOfVertice, static_cast<size_t>(-1));
        
        parent[startVertex] = startVertex;
        distance[startVertex] = static_cast<typename Edge::PathType>(Edge::PATH_ZERO);
        
        std::set<std::pair<typename Edge::PathType, size_t> > queue;
        
        queue.insert(std::make_pair(distance[startVertex], startVertex));
        
        while (queue.size())
        {
            size_t vertex = queue.begin()->second;
            queue.erase(queue.begin());
            for (auto const &edge: adjacencyList[vertex])
            {
                if (distance[edge.getDestination()] > Edge::recalculate(distance[vertex], edge))
                {
                    queue.erase(std::make_pair(distance[edge.getDestination()], edge.getDestination()));
                    distance[edge.getDestination()] = Edge::recalculate(distance[vertex], edge);
                    parent[edge.getDestination()] = vertex;
                    queue.insert(std::make_pair(distance[edge.getDestination()], edge.getDestination()));
                }
            }
        }
        return std::make_pair(distance, parent);
    }
    
    std::vector<size_t> restorePath(const std::vector<size_t> &parent, size_t endVertex)
    {
        std::vector<size_t> answer;
        do
        {
            answer.push_back(endVertex);
            endVertex = parent[endVertex];
        }
        while (parent[endVertex] != endVertex);
        std::reverse(answer.begin(), answer.end());
        return answer;
    }
    
    size_t getNumberOfVertice() const
    {
        return numberOfVertice;
    }
};

#endif