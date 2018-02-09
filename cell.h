#ifndef _CELL_H_
#define _CELL_H_

#include <utility>
#include <iostream>

#include "observer.h"


class Block;
class Subject;

class Cell:public Observer {
  std::pair<int, int> coord;
  Block *block;
  
 public:
  Cell(int row, int col);
  std::pair<int, int> getCoord(); // Returns coords
  Block* getBlock();
  void setBlock(Block* newBlock);
  char getGlyph(); // Returns the letter that this cell should be represented by
  
  void notify();
  void notify(Subject*);
};

#endif
