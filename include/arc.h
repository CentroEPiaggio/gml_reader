#ifndef ARC_H
#define ARC_H

#include <string>
#include "node.h"
#include <ostream>
#include <fstream>
namespace gml_utils
{
class arc
{

  
  void readLabelGraphics( std::ifstream& f );
  
  
public:
  int first;
  int second;
  double len;
  int index;
  std::string name;
    arc();
    
    virtual ~arc();
    
    friend std::ostream &operator<<( std::ostream &out, const arc &a );
    void read(std::ifstream& f);
    void write(std::ofstream& f);
};
}
#endif // ARC_H
