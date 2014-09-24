#include "cell.h"
using namespace std;

Cell::Cell(): occupied(false),
              occupier(0),
   	      occupierType(' '){}

Cell &Cell::operator=(const Cell &other){
  if(this == &other) return *this;
  else{
    occupied = other.occupied;
    occupier = other.occupier;
    occupierType = other.occupierType;
    return *this;
  }
}

void Cell::changeCell(bool ocpd, Block *ocpr, char ot){
  occupied = ocpd;
  occupier = ocpr;
  occupierType = ot;
}

Block* Cell::getOccupier(){ return occupier; }

bool Cell::getOccupied() { return occupied; }

char Cell::getOccupierType() { return occupierType; }

void Cell::notifyBlock(){
  occupier->notify();
}
