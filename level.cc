#include "level.h"
#include <cstdlib>
#include <ctime>
#include <cstdlib>
using namespace std;

Level::Level(): currentLvl(1){}

Level::Level(int currentLvl): currentLvl(currentLvl){}

int Level::getCurrentLvl(){ return currentLvl; }

void Level:: setCurrentLvl(int newLvl){ currentLvl = newLvl; }

char Level::generator(int I, int J, int L, int O, int S, int Z, int T){
  int weightI = I;
  int weightJ = weightI + J;
  int weightL = weightJ + L;
  int weightO = weightL + O;
  int weightS = weightO + S;
  int weightZ = weightS + Z;
  int weightT = weightZ + T;
  int total = weightT;
  srand(time(0));
  int randomNum = 1 + (rand() % total);
  if(randomNum <= weightI) return 'I';
  else if(randomNum <= weightJ) return 'J';
  else if(randomNum <= weightL) return 'L';
  else if(randomNum <= weightO) return 'O';
  else if(randomNum <= weightS) return 'S';
  else if(randomNum <= weightZ) return 'Z';
  else return 'T';
}

char Level::lvlOne(){ return generator(2, 2, 2, 2, 1, 1, 2); }

char Level::lvlTwo(){ return generator(1, 1, 1, 1, 1, 1, 1); }

char Level::lvlThree(){ return generator(1, 1, 1, 1, 2, 2, 1); }
