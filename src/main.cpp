#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

using namespace gml_utils;

void read(std::ifstream* f,graph& g)
{
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
    return;
}

int main(int argc, char **argv) {
    graph g;
    ifstream f;
    if (argc<2)
    {
        cout<< "usage: gml_to_lgf filename.gml"<<endl;
        return 1;
    }
    string filename=argv[1];
    cout<<filename<<endl;
    
    f.open(filename.c_str(),ios::in);
    read(&f,g);
    
    f.close();
    ofstream fo;
    fo.open(filename.append(".lgf").c_str(),ios::out);
    fo<<g.tolgf();
    fo.close(); 
    return 0;
}
