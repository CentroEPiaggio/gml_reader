#ifndef ARC_H
#define ARC_H

#include <string>
#include "node.h"
#include <ostream>
#include <fstream>

class arc
{

  
  void readLabelGraphics( std::ifstream* f );
  
  
public:
  int first;
  int second;
  double len;
  int index;
  std::string name;
    arc();
    
    virtual ~arc();
    
    friend std::ostream &operator<<( std::ostream &out, const arc &a );
    void readArc(std::ifstream* arg1);

};

#endif // ARC_H
