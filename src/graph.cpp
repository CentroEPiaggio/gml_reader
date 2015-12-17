#include "graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "utils.h"

using namespace std;
using namespace gml_utils;

graph::graph()
{

}


void graph::readGraph(ifstream& f)
{
  char s[256];
  f.getline(s,256);
  string tmp=s;
  if (tmp.compare("[")==0) //deve esserci subito una quadra
  {
	int numArc=0;
    while(!f.eof()) //leggiamo i nodi e gli archi
    {
      f.getline(s,256);
      tmp=s;
      tmp.erase(remove(tmp.begin(), tmp.end(), ' '),tmp.end());
      tmp.erase(remove(tmp.begin(), tmp.end(), '\t'),tmp.end());
      if (tmp.compare("node")==0)
      {
	 node n;
	 n.read(f);
	 nodes.push_back(n);
	 continue;
      }
      if (tmp.compare("edge")==0)
      {
	arc a;
	a.read(f);
	stringstream s;
	s<<numArc;
	numArc++;
	a.name=s.str();
        a.index=numArc;
	arcs.push_back(a);
	continue;
      }
      if (tmp.find("[")==0)
      {
	utils::skipSection(f);
	continue;
      }
      if (tmp.find("]")==0)
      {
	 break;
      }
    }
  }
  else
  {
  cerr<<"impossibile trovare la [ di apertura del graph"<<endl;
  }
}

namespace gml_utils{

ostream &operator<<( ostream &out, const graph &g ){
  out<<"@nodes"<<endl;
  out<<"label\tcoordinates_x\tcoordinates_y"<<endl;
  for (unsigned int i=0;i<g.nodes.size();i++)
    out<<g.nodes[i]<<endl;
  out<<"@arcs"<<endl;
  out<<"\t\tlabel\tlength"<<endl;
  for (unsigned int i=0;i<g.arcs.size();i++)
    out<<g.arcs[i]<<endl;
  return out;
}

}

string graph::tolgf()
{
  stringstream out;
  out<<"@nodes"<<endl;
  out<<"label\tcoordinates_x\tcoordinates_y"<<endl;
  for (unsigned int i=0;i<nodes.size();i++)
    out<<nodes[i]<<endl;
  out<<"@arcs"<<endl;
  out<<"\t\tlabel\tlength"<<endl;
  for (unsigned int i=0;i<arcs.size();i++)
    out<<arcs[i]<<endl;
  return out.str();

}


graph::~graph()
{

}

