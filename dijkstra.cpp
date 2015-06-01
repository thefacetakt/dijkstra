#include <iostream>
#include <random>
#include "dijkstra.hpp"
#include "fordBellman.hpp"
#include "StringEdge.hpp"

std::default_random_engine generator;

const size_t MAX_PERCENTAGE = 100;

const size_t STRING_LENGTH = 5;
const size_t ALPHABET_SIZE = 26;
const size_t MAX_VERTEX_PROCESSED = 5;
std::string generateRandomString()
{
    std::uniform_int_distribution<char> charGetter(0, ALPHABET_SIZE - 1);
    std::string result(STRING_LENGTH, '\0');
    for (size_t i = 0; i < STRING_LENGTH; ++i)
    {
        result[i] = charGetter(generator) + 'a';
    }
    return result;
}

Graph<StringEdge> generateRandomGraph(size_t percentageOfEdge, size_t numberOfVertice)
{
    std::uniform_int_distribution<size_t> percentageGetter(0, MAX_PERCENTAGE - 1);
    Graph<StringEdge> result(numberOfVertice);
    for (int i = 0; i < numberOfVertice; ++i)
    {
        for (int j = 0; j < numberOfVertice; ++j)
        {
            if (percentageGetter(generator) < percentageOfEdge)
            {
                result.addOrientedEdge(i, j, generateRandomString());
            }
        }
    }
    return result;
}

void test()
{
    for (size_t size = 1; size < 625; size *= 5)
    {
        std::uniform_int_distribution<size_t> sizeGetter(size, 5 * size);
        
        for (size_t curPercentage = 0; curPercentage < MAX_PERCENTAGE; curPercentage += 10)
        {
            std::uniform_int_distribution<size_t> percentageGetter(curPercentage, curPercentage + 10);
            size_t percentage = percentageGetter(generator);
            Graph<StringEdge> graph = generateRandomGraph(percentage, sizeGetter(generator));
            std::vector<size_t> vertice;
            for (size_t vertex = 0; vertex < graph.getNumberOfVertice(); ++vertex)
            {
                vertice.push_back(vertex);
            }
            std::random_shuffle(vertice.begin(), vertice.end());
            vertice.resize(std::min(MAX_VERTEX_PROCESSED, vertice.size()));
            for (auto &vertex: vertice)
            {
                if (graph.dijkstra(vertex) != fordBellman(vertex, graph))
                {
                    printf("ERROR TEST %zu %zu %zu\n", graph.getNumberOfVertice(), percentage, vertex);
                    return;
                }
                printf("OK TEST %zu %zu %zu\n", graph.getNumberOfVertice(), percentage, vertex);
            }
        }
    }
}

int main()
{
    generator.seed(1);
    test();
    return 0;
}