#ifndef _STRING_EDGE
#define _STRING_EDGE

#include <string>


//Edge function is a word consisting only from small latin letters
class StringEdge
{
public:
    typedef std::string WeightType;
    typedef std::string PathType;
    static const PathType PATH_INFINITY;
    static const PathType PATH_ZERO;
private:
    size_t destination;
    WeightType weight;
public:
    StringEdge(size_t destination, WeightType weight) : destination(destination), weight(weight)
    {
    }
    
    static PathType recalculate(PathType path, StringEdge edge)
    {
        return path + edge.weight;
    }
    
    size_t getDestination() const
    {
        return destination;
    }
    
    WeightType getWeight() const
    {
        return weight;
    }
};

const std::string StringEdge::PATH_INFINITY = std::string(1, 'z' + 1);
const std::string StringEdge::PATH_ZERO = "";
#endif