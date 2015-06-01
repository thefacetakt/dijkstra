#ifndef _REGULAR_EDGE
#define _REGULAR_EDGE

#include <climits>

class RegularEdge
{
public:
    typedef size_t WeightType;
    typedef unsigned long long PathType;
    static const PathType PATH_INFINITY = ULLONG_MAX;
    static const PathType PATH_ZERO = 0llu;
private:
    size_t destination;
    WeightType weight;
    
public:
    RegularEdge(size_t destination, WeightType weight) : destination(destination), weight(weight)
    {
    }
    
    static PathType recalculate(PathType path, RegularEdge edge)
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

#endif