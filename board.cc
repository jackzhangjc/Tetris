#include <iostream>
#include "board.h"
#include "block.h"
#include "cell.h"
#include "textdisplay.h"
#include "posn.h"
#include "window.h"
using namespace std;

Board::Board(){
  td = new TextDisplay();
  theBoard = new Cell*[18];
  for(int row=0; row < 18; row++){
    theBoard[row] = new Cell[10];
  }
  level = new Level(1);
  score=new Score();
  w = new Xwindow();
  for (int row=0; row<18; row++){
    for (int col=0; col<10; col++){
      w->fillRectangle(col*50,row*50,50,50,1);
    }
  }
}

Board::~Board(){
  for(int row=0; row < 18; row++){
    delete [] theBoard[row];
  }
  delete w;
}

void Board::placeIn(Block *b){
  for(int i=0; i<4; i++){
    theBoard[b->getP()[i].x][b->getP()[i].y].changeCell(true, b, b->getType());
    td->notify(b->getP()[i].x, b->getP()[i].y, true, b->getType());
    draw(b->getP()[i].x, b->getP()[i].y, b->getType());
  }
}

void Board::clearBlock(Block *b){
  for(int i=0; i<4; i++){
    theBoard[b->getP()[i].x][b->getP()[i].y].changeCell(false, 0, ' ');
    td->notify(b->getP()[i].x, b->getP()[i].y, false, ' ');
    draw(b->getP()[i].x, b->getP()[i].y, ' ');
  }
}

bool Board::checkMove(Block *b, string dir){
  for(int i=0; i<4; i++){
    if(dir=="d"){
      if(b->getP()[i].x+1 > 17 ||
	 (theBoard[b->getP()[i].x+1][b->getP()[i].y].getOccupied() &&
	  theBoard[b->getP()[i].x+1][b->getP()[i].y].getOccupier() != b)){
	return false;
      }
    }
    else if(dir=="l"){
      if(b->getP()[i].y-1 < 0 ||
	 (theBoard[b->getP()[i].x][b->getP()[i].y-1].getOccupied() &&
	  theBoard[b->getP()[i].x][b->getP()[i].y-1].getOccupier() != b)){
	return false;
      }
    }
    else if(dir=="r"){
      if(b->getP()[i].y+1 > 9 ||
	 (theBoard[b->getP()[i].x][b->getP()[i].y+1].getOccupied() &&
	  theBoard[b->getP()[i].x][b->getP()[i].y+1].getOccupier() != b)){
	return false;
      }
    }
    else{
      Posn *temp;
      if(dir=="clockwise") temp = b->rotatedP("clockwise");
      else temp = b->rotatedP("counterclockwise");
      for(int i=0; i<4; i++){
	if((temp[i].x < 0 || temp[i].y > 9) ||
           (theBoard[temp[i].x][temp[i].y].getOccupied() &&
            theBoard[temp[i].x][temp[i].y].getOccupier() != b)){
	  delete temp;
	  return false;
	}
      }
    }
  }
  return true;
}

void Board::moveBlock(Block *b, char dir){
  clearBlock(b);
  b->move(dir);
  placeIn(b);
}

Block* Board::blockGenerator(int lvl){
  char blockType;
  if(lvl == 1) blockType = level->lvlOne();
  else if(lvl == 2) blockType = level->lvlTwo();
  else blockType = level->lvlThree();
  Block *newBlock = new Block(blockType,lvl);
  for(int i=0; i<4; i++){
    if(theBoard[newBlock->getP()[i].x][newBlock->getP()[i].y].getOccupied()){
      delete newBlock;
      return NULL;
    }
  }
  placeIn(newBlock);
  return newBlock;
}

int Board::findRowFull(){
  int numCells = 0;
  int rowFull = -1;
  for(int row=17; row > 0; row--){
    for(int col=0; col < 10; col++){
      if(theBoard[row][col].getOccupied()) numCells++;
    }
    if(numCells == 10){
      rowFull = row;
      break;
    }      
    else numCells = 0;
  }
  return rowFull;
}

void Board::clearRow(){
  int rowNum=0;
  while(true){
    int fullRow = findRowFull();
    if(fullRow != -1){
      rowNum++;
      for(int i=0; i < 10; i++){
        theBoard[fullRow][i].notifyBlock();
        if (theBoard[fullRow][i].getOccupier()->isCleared()){
          //cout<<"a";
          int previousDiff=theBoard[fullRow][i].getOccupier()->getDifficulty();
          int current=score->getScore()+(previousDiff+1)*(previousDiff+1);
          score->setScore(current);
          score->setHiScore(current);
        }
        theBoard[fullRow][i].changeCell(false, NULL, ' ');
	td->notify(fullRow, i, false, ' ');
	draw(fullRow, i, ' ');
      }
      for(int row=fullRow; row > 1; row--){
	for(int col=0; col < 10; col++){
	  theBoard[row][col] = theBoard[row-1][col];
	  td->notify(row, 
		     col, 
		     theBoard[row-1][col].getOccupied(), 
		     theBoard[row-1][col].getOccupierType());
	  draw(row, col, theBoard[row-1][col].getOccupierType());
	}
      }
    }
    else break;
  }
  if (rowNum>0){
    int current=score->getScore()+(rowNum+level->getCurrentLvl())*(rowNum+level->getCurrentLvl());
    score->setScore(current);
    score->setHiScore(current);
  }
}
	  
void Board::rotate(Block *b, string dir){
  Posn *temp = b->rotatedP(dir);
  clearBlock(b);
  b->setP(temp);
  delete temp;
  placeIn(b);
}

int Board::getLvl() const { return level->getCurrentLvl(); }

void Board::setLvl(int newLvl){ level->setCurrentLvl(newLvl); }

int Board::getScore() const{
  return score->getScore();
}

int Board::getHiScore() const{
  return score->getHiScore();
}
void Board::draw(int x, int y, char type){
  int color;
  if(type == 'I') color = 2;
  else if(type == 'J') color = 3;
  else if(type == 'L') color = 4;
  else if(type == 'O') color = 5;
  else if(type == 'S') color = 6;
  else if(type == 'Z') color = 7;
  else if(type == 'T') color = 8;
  else if(type == ' ') color = 1;
  w->fillRectangle(y*50, x*50, 48, 48, color);
  //w->fillRectangle(y*50-12, x*50-12, 4, 4, 0);
}

ostream& operator<<(ostream &out, const Board &b){
  out<<"Level: "<<b.getLvl();
  out<<" Score: "<<b.getScore();
  cout<<" Hi Score: "<<b.getHiScore(); 
  //out << *(b.td);
  out << endl;
  return out;
}

