Dijkstra implementation
===========================
This is a simple O(ElogV) implementation of Dijkstra algorithm, working for every path function possible
To use algo (dijkstra.hpp) you should implement class Edge with:
* defined WeightType and PathType classes
* defined constants PATH_INFINITY and PATH_ZERO
* constructor from destination (size_t) and weight (WeightType)
* static PathType recalculate function: which takes PathType and Edge and returns PathType (which represents path, obtained by adding a new edge (second argument) to existing path (first argument)
* getDestination and getWeight const methonds


It works!
Here some examples:

* If use RegularEdge.hpp, the result can be seen [here](http://informatics.mccme.ru/moodle/mod/statements/view3.php?chapterid=3494&run_id=1760r7895#1) (submission id 1760-7895)

* If use BusEdge.hpp, the result can be seen [here](http://informatics.mccme.ru/mod/statements/view3.php?id=10845&chapterid=170#1) (submission id 85-3214)

* If use StringEdge.hpp, just trust [my random tests](https://github.com/thefacetakt/dijkstra/blob/master/dijkstra.cpp)


