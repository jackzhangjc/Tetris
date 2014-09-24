#ifndef __LEVEL_H__
#define __LEVEL_H__

class Level{
  int currentLvl;
  char generator(int I, int J, int L, int O, int S, int Z, int T);
 public:
  Level();
  Level(int currentLvl);
  int getCurrentLvl();
  void setCurrentLvl(int newLvl);
  char lvlOne();
  char lvlTwo();
  char lvlThree();
};

#endif
