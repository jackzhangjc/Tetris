#include "block.h"
#include "posn.h"
#include <iostream>
using namespace std;

Block::Block(char type,int difficulty):type(type){
  this->difficulty=difficulty;
  blockNum=4;
  p = new Posn[4];
  if(type=='I'){
    p[0] = Posn(3,0);
    p[1] = Posn(3,1);
    p[2] = Posn(3,2);
    p[3] = Posn(3,3);
  }
  else if(type=='J'){
    p[0] = Posn(3,0);
    p[1] = Posn(4,0);
    p[2] = Posn(4,1);
    p[3] = Posn(4,2);
  }
  else if(type=='L'){
    p[0] = Posn(3,2);
    p[1] = Posn(4,0);
    p[2] = Posn(4,1);
    p[3] = Posn(4,2);
  }
  else if(type=='O'){
    p[0] = Posn(3,0);
    p[1] = Posn(3,1);
    p[2] = Posn(4,0);
    p[3] = Posn(4,1);
  }
  else if(type=='S'){
    p[0] = Posn(3,1);
    p[1] = Posn(3,2);
    p[2] = Posn(4,0);
    p[3] = Posn(4,1);
  }
  else if(type=='Z'){
    p[0] = Posn(3,0);
    p[1] = Posn(3,1);
    p[2] = Posn(4,1);
    p[3] = Posn(4,2);
  }
  else{  
    p[0] = Posn(4,1);
    p[1] = Posn(3,0);
    p[2] = Posn(3,1);
    p[3] = Posn(3,2);
  }
}

Block::~Block(){
  delete []p;
}

char Block::getType(){ return type; }

void Block::move(char dir){
  for(int i=0; i<4; i++){
    if(dir == 'l') p[i].y -= 1;
    else if(dir == 'r') p[i].y += 1;
    else p[i].x += 1;
  }
}

bool Block::isCleared(){
  if (blockNum==0){
    return true;
  } else {
    return false;
  }
}

void Block::notify(){
  blockNum--;
}

Posn* Block::getP(){ return p; }

Posn* Block::rotatedP(string dir){
  int xMaxBefore = -100;
  int yMinBefore = 100;
  int xMaxAfter = -100;
  int yMinAfter = 100;
  int temp, xDist, yDist;
  Posn *newP = new Posn[4];
  for(int i=0; i<4; i++){
    newP[i] = p[i];
  }
  //find xMaxBefore and yMinBefore:
  for(int i=0; i<4; i++){
    xMaxBefore = max(newP[i].x, xMaxBefore);
    yMinBefore = min(newP[i].y, yMinBefore);
  }
  //find new Posns after rotation:
  if(dir == "clockwise"){
    for(int i=0; i<4; i++){
      temp = newP[i].x;
      newP[i].x = newP[i].y;
      newP[i].y = -temp;
    }
  }
  else{
    for(int i=0; i<4; i++){
      temp = newP[i].x;
      newP[i].x = -newP[i].y;
      newP[i].y = temp;
    }
  }
  //find xMaxAfter and yMinAfter:
  for(int i=0; i<4; i++){
    xMaxAfter = max(newP[i].x, xMaxAfter);
    yMinAfter = min(newP[i].y, yMinAfter);
  }
  //compute xDist and yDist:
  xDist = xMaxAfter - xMaxBefore;
  yDist = yMinAfter - yMinBefore;
  //put the Posns back to the correct place:
  for(int i=0; i<4; i++){
    newP[i].x -= xDist;
    newP[i].y -= yDist;
  }
  return newP;
}

void Block::setP(Posn *newPosn){
  for(int i=0; i<4; i++){
    p[i] = newPosn[i];
  }
}

int Block::getDifficulty(){
  return difficulty;
}
