#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "textdisplay.h"
#include "level.h"
#include "window.h"
#include "score.h"
 

class Board{
  Cell **theBoard;
  TextDisplay *td;
  Level *level;
  Score *score;
  Xwindow *w;
  int findRowFull();
  void draw(int x, int y, char type);
 public:
  Board();
  ~Board();
  void placeIn(Block *b);
  void clearBlock(Block *b);
  void moveBlock(Block *b, char dir);
  void rotate(Block *b, std::string dir);
  bool checkMove(Block *b, std::string dir);
  Block* blockGenerator(int lvl);
  void clearRow();
  int getLvl() const;
  void setLvl(int newLvl);
  int getScore() const;
  int getHiScore() const;

  friend std::ostream& operator<<(std::ostream &out, const Board &b);
};

#endif
