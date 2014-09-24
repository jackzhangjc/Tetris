#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(){
  theDisplay = new char*[18];
  for(int row=0; row < 18; row++){
    theDisplay[row] = new char[10];
  }
  for(int row=0; row < 18; row++){
    for(int col=0; col < 10; col++){
      theDisplay[row][col] = '.';
    }
  }
}

void TextDisplay::notify(int x, int y, bool occupied, char type){
  if(occupied) theDisplay[x][y] = type;
  else theDisplay[x][y] = ' ';
}

TextDisplay::~TextDisplay(){
  for(int row=0; row < 18; row++){
    delete [] theDisplay[row];
  }
  delete []theDisplay;
}

ostream& operator<<(ostream &out, const TextDisplay &td){
  for(int row=0; row < 18; row++){
    for(int col=0; col < 10; col++){
      out << td.theDisplay[row][col];
    }
    out << endl;
  }
  return out;
}
