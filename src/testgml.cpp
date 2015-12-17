#include <iostream>
#include <fstream>
#include <lemon/smart_graph.h>
#include <lemon/graph_to_eps.h>
#include <lemon/lgf_reader.h>
#include <gmlreader/gmlreader.hpp>
#include <graph_msgs/GeometryGraph.h>
#include <ros/ros.h>
#include <ros/package.h>
// #include <rviz_visual_tools/rviz_visual_tools.h>

using namespace std;
// #define SCALE 0.05 //TODO ros param

int main(int argc, char **argv) {
    ros::init(argc,argv,"testgml");
    ros::NodeHandle n;
    double scale;
    ros::param::get("graph_scale",scale);
    lemon::SmartDigraph g;
    lemon::SmartDigraph::NodeMap<int> a(g),b(g);
    lemon::SmartDigraph::ArcMap<int> c(g);
    
    if (argc<2)
    {
        cout<< "usage: test_gml filename.gml"<<endl;
        return 1;
    }
    std::string graphName = argv[1];
    std::string path = ros::package::getPath("map_database");
    std::cout<<path<<"/"<<graphName<<std::endl;
    if (graphName.rfind(".lgf")==graphName.length()-4)
    {
        typedef lemon::dim2::Point<int> Point;
        lemon::SmartDigraph::NodeMap<Point> coords(g);
        lemon::DigraphReader<lemon::SmartDigraph>(g, path+"/"+graphName).
        nodeMap("coordinates",coords).
        run();
        for (lemon::SmartDigraph::NodeIt n(g);n!=lemon::INVALID;++n)
        {
            a[n]=coords[n].x;
            b[n]=coords[n].y;
        }
    }
    if (graphName.rfind(".gml")==graphName.length()-4)
    {
        ifstream f;
        f.open((path+"/"+graphName).c_str(),ios::in);
        if (f.fail()) abort();
        lemongmlreader reader;
        reader.read(f,g);
        reader.getCoordx(a);
        reader.getCoordy(b);
        reader.getArcLength(c);
        f.close();
    }
    graph_msgs::GeometryGraph g_msg;
    
    std::map<int,int> nodes_id_to_index;
    
    lemon::SmartDigraph::NodeMap<lemon::dim2::Point<int>> coords(g);
    lemon::SmartDigraph::NodeMap<int> id(g);
    for (lemon::SmartDigraph::NodeIt n(g);n!=lemon::INVALID;++n)
    {
        coords[n].x=a[n];
        coords[n].y=b[n];
        id[n]=g.id(n);
        geometry_msgs::Point p;
        graph_msgs::Edges empty_edge;
        p.x=scale*double(a[n]);
        p.y=scale*double(b[n]);
        p.z=id[n];
        g_msg.nodes.push_back(p);
        g_msg.edges.push_back(empty_edge);
        nodes_id_to_index[id[n]]=g_msg.nodes.size()-1;
    }
    
    for (int i=0;i<g_msg.nodes.size();i++)
    {
        std::vector<uint32_t> edges;
        for ( lemon::SmartDigraph::OutArcIt arcit( g,g.nodeFromId(int(g_msg.nodes[i].z)) ); arcit!=lemon::INVALID; ++arcit )
        {
            edges.push_back(nodes_id_to_index[g.id(g.target(arcit))]);
        }
        g_msg.edges[i].node_ids=edges;
    }    
        
    ros::Publisher pub = n.advertise<graph_msgs::GeometryGraph>("graph_to_rviz",1);
    ros::AsyncSpinner as(1);as.start();
    while(ros::ok())
    {
        sleep(10);
        pub.publish(g_msg);
    }
//     for (auto& p:g_msg.nodes)
//         p.z=0;
//     rviz_visual_tools::RvizVisualTools tools("map","graph_markers");
//     tools.publishGraph(g_msg,rviz_visual_tools::GREY,0.2);
//     sleep(1);
//     lemon::graphToEps<lemon::SmartDigraph> ( g,"image.eps" ).
//     coords ( coords ).
//     nodeTexts ( id ).
//     nodeTextSize ( 4 ).
//     nodeScale ( 0.008 ).
//     arcWidthScale ( 0.0008 ).
//     drawArrows ( true ).
//     arrowWidth ( 3 ).
//     arrowLength ( 5 ).
//     enableParallel ( true ).
//     distantColorNodeTexts().
//     run();
//     
    std::cout << "A digraph is read from "<<graphName << std::endl;
    std::cout << "Number of nodes: " << lemon::countNodes ( g ) << std::endl;
    std::cout << "Number of arcs: " << lemon::countArcs ( g ) << std::endl;
    return 0;
}
