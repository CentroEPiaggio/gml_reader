#ifndef GMLREADER_HPP
#define GMLREADER_HPP
#include "graph.h"
#include <fstream>
#include <map>
#include <lemon/smart_graph.h>

class gmlreader
{
    gml_utils::graph g;
    lemon::SmartDigraph* graph_p;
    std::map<int,int> node_to_lemonId;
    std::map<int,int> arc_to_lemonId;
public:
    gmlreader()
    {

    };

    const gmlreader& read(std::ifstream* f,lemon::SmartDigraph& graph)
    {
        graph_p=&graph;
        std::string tmp;
        char s[256];
        while (!f->eof())
        {
            f->getline(s,256);
            tmp=s;
            if (tmp.compare("graph")==0) //inizia il testo interessante
            {
                g.readGraph(f);
            }
        }
        //convert g to lemon graph
        for (auto node : g.nodes)
        {
            auto n = graph.addNode();
            node_to_lemonId[node.index]=graph.id(n);
        }
        for (auto arc: g.arcs )
        {
            auto a = graph.addArc(graph.nodeFromId(node_to_lemonId[arc.first]),graph.nodeFromId(node_to_lemonId[arc.second]));
            arc_to_lemonId[arc.index]=graph.id(a);
        }
        return *this;
    }
    
    const gmlreader& getCoordx(lemon::SmartDigraph::NodeMap<int>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.x;
        }
    }

    const gmlreader& getCoordx(lemon::SmartDigraph::NodeMap<double>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.x;
        }
    }
    
    const gmlreader& getCoordy(lemon::SmartDigraph::NodeMap<int>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.y;
        }
    }
    
    const gmlreader& getCoordy(lemon::SmartDigraph::NodeMap<double>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.y;
        }
    }
    const gmlreader& getArcLength(lemon::SmartDigraph::ArcMap<int>& map)
    {
        for (auto arc: g.arcs )
        {
            map[graph_p->arcFromId(node_to_lemonId[arc.index])]=arc.len;
        }
    }
    const gmlreader& getArcLength(lemon::SmartDigraph::ArcMap<double>& map)
    {
        for (auto arc: g.arcs )
        {
            map[graph_p->arcFromId(node_to_lemonId[arc.index])]=arc.len;
        }
    }
    
};
      
#endif