#ifndef GMLREADER_HPP
#define GMLREADER_HPP
#include "graph.h"
#include <fstream>
#include <map>

class gmlreader
{
    gml_utils::graph g;
public:
    gmlreader()
    {

    };

    void read(std::ifstream& f)
    {
        std::string tmp;
        char s[256];
        while (!f.eof())
        {
            f.getline(s,256);
            tmp=s;
            if (tmp.compare("graph")==0) //inizia il testo interessante
            {
                g.readGraph(f);
            }
        }
    }
    
    gml_utils::graph getGraph()
    {
        return g;
    }
};
      
#endif