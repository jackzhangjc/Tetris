#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <string>
#include "posn.h"

class Block{
  char type;
  Posn *p;
  int blockNum;
  int difficulty;
 public:
  char getType();
  Posn *getP();
  int getDifficulty();
  bool isCleared();
  void notify();
  Posn *rotatedP(std::string dir);
  void setP(Posn *newPosn);
  void move(char dir);
  Block(char type,int difficulty);  
  ~Block();
};

#endif
