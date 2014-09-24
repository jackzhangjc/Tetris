#ifndef __CELL_H__
#define __CELL_H__
#include "block.h"

class Cell{
  bool occupied;
  Block *occupier;
  char occupierType;
 public:
  Cell();
  Cell(bool ocpd, Block *ocpr, char ot);
  Cell &operator=(const Cell&);
  void changeCell(bool ocpd, Block *ocpr, char ot);
  Block* getOccupier();
  void notifyBlock();
  bool getOccupied();
  char getOccupierType();  
};

#endif
