#include <iostream>
#include <fstream>
#include <lemon/smart_graph.h>
#include <lemon/graph_to_eps.h>
#include <gmlreader/gmlreader.hpp>

using namespace std;

int main(int argc, char **argv) {
    lemon::SmartDigraph g;
    lemon::SmartDigraph::NodeMap<int> a(g),b(g);
    lemon::SmartDigraph::ArcMap<int> c(g);
    ifstream f;
    if (argc<2)
    {
        cout<< "usage: test_gml filename.gml"<<endl;
        return 1;
    }
    string filename=argv[1];
    cout<<filename<<endl;
    
    f.open(filename.c_str(),ios::in);
    
    gmlreader reader;
    reader.read(&f,g);
    reader.getCoordx(a);
    reader.getCoordy(b);
    reader.getArcLength(c);
    
    f.close();

    lemon::SmartDigraph::NodeMap<lemon::dim2::Point<int>> coords(g);
    lemon::SmartDigraph::NodeMap<int> id(g);
    for (lemon::SmartDigraph::NodeIt n(g);n!=lemon::INVALID;++n)
    {
        coords[n].x=a[n];
        coords[n].y=b[n];
        id[n]=g.id(n);
    }
    
    lemon::graphToEps<lemon::SmartDigraph> ( g,"image.eps" ).
    coords ( coords ).
    nodeTexts ( id ).
    nodeTextSize ( 4 ).
    nodeScale ( 0.008 ).
    arcWidthScale ( 0.0008 ).
    drawArrows ( true ).
    arrowWidth ( 3 ).
    arrowLength ( 5 ).
    enableParallel ( true ).
    distantColorNodeTexts().
    run();
    
    std::cout << "A digraph is read from "<<filename << std::endl;
    std::cout << "Number of nodes: " << lemon::countNodes ( g ) << std::endl;
    std::cout << "Number of arcs: " << lemon::countArcs ( g ) << std::endl;
    return 0;
}
