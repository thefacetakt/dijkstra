#ifndef _BUS_EDGE
#define _BUS_EDGE

#include <climits>

class BusEdge
{
public:
    
    struct WeightType
    {
        size_t startTime;
        size_t endTime;
    };
    
    typedef unsigned long long PathType;
    static const PathType PATH_INFINITY = ULLONG_MAX;
    static const PathType PATH_ZERO = 0llu;
private:
    size_t destination;
    WeightType weight;
public:
    BusEdge(size_t destination, WeightType weight) : destination(destination), weight(weight)
    {
    }
    
    static PathType recalculate(PathType path, BusEdge edge)
    {
        if (path <= edge.getWeight().startTime)
            return edge.getWeight().endTime;
        return PATH_INFINITY;
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