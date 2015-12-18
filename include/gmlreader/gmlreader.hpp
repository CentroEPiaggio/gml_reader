#ifndef GMLREADER_HPP
#define GMLREADER_HPP
#include "graph.h"
#include <fstream>
#include <map>
#include <iostream>

class gmlreader
{
    gml_utils::graph g;
public:
    gmlreader()
    {

    };

    bool read(std::ifstream& f)
    {
        std::string tmp;
        bool graph_read=false;
        char s[256];
        while (!(f.eof() || f.bad() || f.fail()))
        {
            f.getline(s,256);
            tmp=s;
            if (tmp.compare("graph")==0)
            {
                graph_read = g.readGraph(f);
                std::cout<<graph_read<<std::endl;
            }
        }
        return graph_read;
    }
    
    gml_utils::graph getGraph()
    {
        return g;
    }
};
      
#endif