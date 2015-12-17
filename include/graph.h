#ifndef GRAPH_H
#define GRAPH_H

#include "arc.h"
#include "node.h"
#include <vector>
#include <fstream>
#include <ostream>
#include <map>

namespace gml_utils
{
    
class graph
{
public:

    std::vector<node> nodes;
    std::vector<arc> arcs;
    std::map<int,node> index_to_nodes;


    graph();
    virtual ~graph();


    friend std::ostream &operator<<( std::ostream &out, const graph &g );
    void readGraph(std::ifstream* arg1);

    std::string tolgf();

};

}
#endif // GRAPH_H
