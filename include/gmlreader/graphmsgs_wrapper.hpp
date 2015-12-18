#ifndef GRAPHMSGS_WRAPPER_HPP
#define GRAPHMSGS_WRAPPER_HPP
#include "gmlreader/gmlreader.hpp"
#include <graph_msgs/GeometryGraph.h>

class graphmsgs_gml
{
    gmlreader reader;
    std::map<int,int> id_to_index;
public:
    graphmsgs_gml()
    {
        
    }
    
    void convert(const gml_utils::graph& g, graph_msgs::GeometryGraph& gr,double scale=1)
    {
        int i=0;
        for (auto node : g.nodes)
        {
            geometry_msgs::Point p;
            p.x=node.x*scale;
            p.y=node.y*scale;
            gr.nodes.push_back(p);
            id_to_index[node.index]=i++;
        }
        gr.edges.resize(g.nodes.size());
        for (auto arc: g.arcs )
        {
            gr.edges[id_to_index[arc.first]].node_ids.push_back(id_to_index[arc.second]);
        }
    }
    
    bool read(std::ifstream& f,graph_msgs::GeometryGraph& gr,double scale=1)
    {
        bool graph_read = reader.read(f);
        if (!graph_read) return false;
        gml_utils::graph g=reader.getGraph();
        //convert g to lemon graph
	int i=0;
        for (auto node : g.nodes)
        {
            geometry_msgs::Point p;
            p.x=node.x*scale;
            p.y=node.y*scale;
            gr.nodes.push_back(p);
            id_to_index[node.index]=i++;
        }
        gr.edges.resize(g.nodes.size());
        for (auto arc: g.arcs )
        {
            gr.edges[id_to_index[arc.first]].node_ids.push_back(id_to_index[arc.second]);
        }
        return true;
    }
    
};

#endif