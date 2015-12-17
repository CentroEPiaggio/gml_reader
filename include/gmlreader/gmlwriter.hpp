#ifndef GMLWRITER_HPP
#define GMLWRITER_HPP
#include "graph.h"
#include <fstream>
#include <map>

/**
 * 
 * 
Creator "yFiles"
Version "2.11"
graph
[
        hierarchic      1
        label   ""
        directed        1
        node
        [
                id      12
                label   "13"
                graphics
                [
                        x       242.0
                        y       561.0
                ]
                LabelGraphics
                [
                        text    "13"
                ]
        ]
        edge
        [
                source  0
                target  1
                graphics
                [
                        fill    "#000000"
                        targetArrow     "standard"
                ]
        ]
]
 * 
 * 
 * 
 */

class gmlwriter
{
    const gml_utils::graph& g;
    std::map<int,int> node_to_lemonId;
    std::map<int,int> arc_to_lemonId;
public:
    gmlwriter(const gml_utils::graph& g):g(g)
    {
    };

    const gmlwriter& write(std::ofstream& f)
    {
        f<<"Creator \"lcr::gmlwriter\"\n version \"0.1\""<<std::endl;
        f<<"graph"<<std::endl;
        f<<"["<<std::endl;
        f<<"        hierarchic      1\n        label   \"\"\n        directed        1"<<std::endl;
        for (auto n:g.nodes)
        {
            n.write(f);
        }
        for (auto a:g.arcs)
        {
            a.write(f);
        }
        f<<"]"<<std::endl;
    }
    
};
      
#endif