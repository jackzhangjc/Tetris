#include "block.h"
#include "posn.h"
#include "board.h"
#include "cell.h"
#include "textdisplay.h"
#include "level.h"
#include "score.h"
#include <iostream>
#include <curses.h>

using namespace std;

int main(int argc, char **argv){
  initscr();
  //cbreak();
  int curse;
  Board *gameBoard = new Board();
  Block *currentBlock = gameBoard->blockGenerator(gameBoard->getLvl());
  //  Block *nextBlock = gameBoard->blockGenerator(gameBoard->getLvl());
  string command;
  int numSettled = 0;
  Block *settledBlocks[100];
  cout << *gameBoard;
  while (true){
    curse=getch();
    if (curse==97){
      if(gameBoard->checkMove(currentBlock, "l")){
        gameBoard->moveBlock(currentBlock, 'l');
      }
    }
    else if(curse==100){
      if(gameBoard->checkMove(currentBlock, "r")){
        gameBoard->moveBlock(currentBlock, 'r');
      }
    }
    else if(curse==115){
      if(!gameBoard->checkMove(currentBlock, "d")){                                                                                                                    
        settledBlocks[numSettled] = currentBlock;                                                                                                                      
        numSettled++;                                                                                                                                                  
        gameBoard->clearRow();                                                                                                                                         
        currentBlock = gameBoard->blockGenerator(gameBoard->getLvl());                                                                                                 
        if(currentBlock == NULL){                                                                                                                                      
          cout << "Game over!" << endl;                                                                                                                                
          return 0;                                                                                                                                                    
        }
      }                                                                                                                                                                
      else gameBoard->moveBlock(currentBlock, 'd');                                                                                                                    
    }
    else if(curse==32){                                                                                                                                        
      while(gameBoard->checkMove(currentBlock, "d")){                                                                                                                  
        gameBoard->moveBlock(currentBlock, 'd');                                                                                                                       
      }
      settledBlocks[numSettled] = currentBlock;                                                                                                                        
      numSettled++;                                                                                                                                                    
      gameBoard->clearRow();                                                                                                                                           
      currentBlock = gameBoard->blockGenerator(gameBoard->getLvl());                                                                                                   
      if(currentBlock == NULL){                                                                                                                                        
        cout << "Game over!" << endl;                                                                                                                                  
        return 0;                                                                                                                                                      
      }
    }
    else if(curse==119){                                                                                                                                          
      if(gameBoard->checkMove(currentBlock, "clockwise")){                                                                                                             
        gameBoard->rotate(currentBlock, "clockwise");                                                                                                                  
      }
    }
    cout<< *gameBoard;
  }
  endwin();
     
  while(cin >> command){
    if(command == "l"){
      if(gameBoard->checkMove(currentBlock, "l")){
	gameBoard->moveBlock(currentBlock, 'l');
      }
    }
    else if(command == "r"){
      if(gameBoard->checkMove(currentBlock, "r")){
	gameBoard->moveBlock(currentBlock, 'r');
      }
    }
    else if(command == "d"){
      if(!gameBoard->checkMove(currentBlock, "d")){
	settledBlocks[numSettled] = currentBlock;
	numSettled++;
	gameBoard->clearRow();
	currentBlock = gameBoard->blockGenerator(gameBoard->getLvl());
	if(currentBlock == NULL){
	  cout << "Game over!" << endl;
	  return 0;
	}
      }      
      else gameBoard->moveBlock(currentBlock, 'd');
    }
    else if(command == "drop"){
      while(gameBoard->checkMove(currentBlock, "d")){
	gameBoard->moveBlock(currentBlock, 'd');
      }
      settledBlocks[numSettled] = currentBlock;
      numSettled++;
      gameBoard->clearRow();
      currentBlock = gameBoard->blockGenerator(gameBoard->getLvl());
      if(currentBlock == NULL){
	cout << "Game over!" << endl;
	return 0;
      }
    }
    else if(command == "cw"){
      if(gameBoard->checkMove(currentBlock, "clockwise")){
	gameBoard->rotate(currentBlock, "clockwise");
      }
    }
    else if(command == "ccw"){
      if(gameBoard->checkMove(currentBlock, "counterclockwise")){
	gameBoard->rotate(currentBlock, "counterclockwise");
      }
    }
    else if(command == "lvlup"){
      int nextLvl = gameBoard->getLvl() + 1;
      if(nextLvl <= 3) gameBoard->setLvl(nextLvl);
      else cout << "Can't be harder!" << endl;
    }
    else if(command == "lvldown"){
      int nextLvl = gameBoard->getLvl() - 1;
      if(nextLvl >= 1) gameBoard->setLvl(nextLvl);
      else cout << "Can't be easier!" << endl;
    }
    else cout << "Not implemented yet!" << endl;
    cout << *gameBoard;
    } 
}

