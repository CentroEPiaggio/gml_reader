#ifndef LEMONWRAPPER_HPP
#define LEMONWRAPPER_HPP
#include "gmlreader/gmlreader.hpp"
#include "gmlwriter.hpp"
#include <lemon/smart_graph.h>
#include <lemon/dim2.h>

class lemon_gml
{
    lemon::SmartDigraph* graph_p;
    gmlreader reader;
    gmlwriter writer;
    gml_utils::graph g;
    std::map<int,int> node_to_lemonId;
    std::map<int,int> arc_to_lemonId;
public:
    lemon_gml():writer(g)
    {
        
    };
    
    void convert(const gml_utils::graph& g, lemon::SmartDigraph& graph)
    {
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
    }
    
    void convert(const lemon::SmartDigraph& gr,lemon::SmartDigraph::NodeMap<lemon::dim2::Point<double>>& coords, gml_utils::graph& g)
    {
        for (lemon::SmartDigraph::NodeIt n(gr);n!=lemon::INVALID;++n)
        {
            gml_utils::node n1;
            n1.x=coords[n].x;
            n1.y=coords[n].y;
            n1.index=gr.id(n);
            g.nodes.push_back(n1);
        }
        
        for ( lemon::SmartDigraph::ArcIt arcit(gr); arcit!=lemon::INVALID; ++arcit )
        {
            gml_utils::arc a;
            a.first=gr.id(gr.source(arcit));
            a.second=gr.id(gr.target(arcit));
            g.arcs.push_back(a);
        }
    }
    
    void convert(const lemon::SmartDigraph& gr,lemon::SmartDigraph::NodeMap<lemon::dim2::Point<int>>& coords, gml_utils::graph& g)
    {
        for (lemon::SmartDigraph::NodeIt n(gr);n!=lemon::INVALID;++n)
        {
            gml_utils::node n1;
            n1.x=coords[n].x;
            n1.y=coords[n].y;
            n1.index=gr.id(n);
            g.nodes.push_back(n1);
        }
        
        for ( lemon::SmartDigraph::ArcIt arcit(gr); arcit!=lemon::INVALID; ++arcit )
        {
            gml_utils::arc a;
            a.first=gr.id(gr.source(arcit));
            a.second=gr.id(gr.target(arcit));
            g.arcs.push_back(a);
        }
    }
    
    void write(std::ofstream& f,lemon::SmartDigraph& graph,lemon::SmartDigraph::NodeMap<lemon::dim2::Point<double>>& coords)
    {
        convert(graph,coords,g);
        writer.write(f);
    }
    
    void read(std::ifstream& f,lemon::SmartDigraph& graph)
    {
        graph_p=&graph;
        reader.read(f);
        g=reader.getGraph();
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
    }
    
    void getCoordx(lemon::SmartDigraph::NodeMap<int>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.x;
        }
    }
    
    void getCoordx(lemon::SmartDigraph::NodeMap<double>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.x;
        }
    }
    
    void getCoordy(lemon::SmartDigraph::NodeMap<int>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.y;
        }
    }
    
    void getCoordy(lemon::SmartDigraph::NodeMap<double>& map)
    {
        for (auto node : g.nodes)
        {
            map[graph_p->nodeFromId(node_to_lemonId[node.index])]=node.y;
        }
    }
    
    void getArcLength(lemon::SmartDigraph::ArcMap<int>& map)
    {
        for (auto arc: g.arcs )
        {
            map[graph_p->arcFromId(node_to_lemonId[arc.index])]=arc.len;
        }
    }
    
    void getArcLength(lemon::SmartDigraph::ArcMap<double>& map)
    {
        for (auto arc: g.arcs )
        {
            map[graph_p->arcFromId(node_to_lemonId[arc.index])]=arc.len;
        }
    }
    
};

#endif