#include "score.h"

Score::Score():currentScore(0),hiScore(0){}

void Score::setScore(int currentScore){
  this->currentScore=currentScore;
}

void Score::setHiScore(int hiScore){
  this->hiScore=hiScore;
}

int Score::getScore(){
  return currentScore;
}

int Score::getHiScore(){
  return hiScore;
}
