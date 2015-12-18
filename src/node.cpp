#include "node.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "utils.h"

using namespace std;
using namespace gml_utils;


node::node()
{
	x=y=0;
}


bool node::readGraphics(ifstream& f)
{
    char s[256];
    f.getline(s,256);
    string tmp;
    tmp=s;
    tmp.erase(remove(tmp.begin(), tmp.end(), ' '),tmp.end());
    tmp.erase(remove(tmp.begin(), tmp.end(), '\t'),tmp.end());
    if (tmp.compare("[")==0) //deve esserci subito una quadra
    {
        while(!f.eof()) //leggiamo le proprietà del nodo
        {
            f.getline(s,256);
            tmp=s;
            tmp.erase(remove(tmp.begin(), tmp.end(), ' '),tmp.end());
            tmp.erase(remove(tmp.begin(), tmp.end(), '\t'),tmp.end());
            if (tmp.find("x")==0)
            {
                stringstream in;
                in<<tmp.substr(1,tmp.length()-1);
                in>>x;
                continue;
            }
            if (tmp.find("y")==0)
            {
                stringstream in;
                in<<tmp.substr(1,tmp.length()-1);
                in>>y;
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
        cerr<<"error, could not find section graphics (missing \"[\" )"<<endl;
        return false;
    }
    return true;
}



bool node::read(ifstream& f)
{
    char s[256];
    f.getline(s,256);
    string tmp=s;
    tmp.erase(remove(tmp.begin(), tmp.end(), ' '),tmp.end());
    tmp.erase(remove(tmp.begin(), tmp.end(), '\t'),tmp.end());
    if (tmp.compare("[")==0) //deve esserci subito una quadra
    {
        while(!f.eof()) //leggiamo le proprietà del nodo
        {
            f.getline(s,256);
            tmp=s;
            tmp.erase(remove(tmp.begin(), tmp.end(), ' '),tmp.end());
            tmp.erase(remove(tmp.begin(), tmp.end(), '\t'),tmp.end());
            
            if (tmp.find("id")==0)
            {
                name=tmp.substr(2,tmp.length()-2);
                index=atoi(name.c_str());
                continue;
            }
            if (tmp.find("label")==0)
            {
                label=tmp.substr(6,tmp.length()-7);
                if (name.compare(label)!=0)
                {
                    //cout<<"ATTENZIONE, rilevato un nodo con id diverso dal label, potrebbero succedere danni, nome:"<<name<<" label:"<<label<<endl;
                }
                continue;
            }
            if (tmp.compare("graphics")==0)
            {
                readGraphics(f);
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
        cerr<<"error, could not find section graphics (missing \"[\" )"<<endl;
        return false;
    }
    return true;
}

namespace gml_utils{
    
ostream &operator<<( ostream &out, const node &n ){
  out<<n.name<<"\t"<<n.x<<"\t"<<n.y;
  return out;
}
}

void node::write(ofstream& f)
{
//     node
//     [
//     id      12
//     label   "13"
//     graphics
//     [
//     x       242.0
//     y       561.0
//     ]
//     LabelGraphics
//     [
//     text    "13"
//     ]
//     ]
    f<<"node"<<std::endl;
    f<<"["<<std::endl;
    {
        f<<"id    "<<index<<std::endl;
        f<<"label    "<<index<<std::endl;
        f<<"graphics"<<std::endl;
        f<<"["<<std::endl;
        {                
            f<<"x    "<<x<<std::endl;
            f<<"y    "<<y<<std::endl;
        }
        f<<"]"<<std::endl;
        f<<"LabelGraphics"<<std::endl;
        f<<"["<<std::endl;
        {
            f<<"text    "<<index<<std::endl;
        }
        f<<"]"<<std::endl;
    }
    f<<"]"<<std::endl;
}


node::~node()
{

}


