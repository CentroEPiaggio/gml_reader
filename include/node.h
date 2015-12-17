#ifndef NODE_H
#define NODE_H

#include <string>
#include <fstream>
#include <ostream>

namespace gml_utils
{
class node
{
  
    std::string label;
    void readGraphics( std::ifstream& f );

public:
    double x,y;
    std::string name;
    int index;
    node();
    virtual ~node();
  
    
    friend std::ostream &operator<<( std::ostream &out, const node &n );
    void read( std::ifstream& f );
    void write(std::ofstream& f);
};
}
#endif // NODE_H
