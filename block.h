#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <string>
#include <utility>
#include <iostream>

#include "subject.h"

class Cell;

class Block:public Subject {
  char glyph;    // This is the glyph that is displayed in the text View
  int levelGenerated;
  std::vector<std::pair<int,int>> CoOrd;

 public:
  Block(char glyph, int levelGenerated);
  
  // ACCESOR
  char getGlyph();
  std::vector<std::pair<int, int>> getCoOrd();
  int getScore(); // Returns points scored when block is cleared
  
 // OPERATION
  void place(std::vector<Cell*> newLoc);
  void clearCoord(std::pair<int,int> p);

};

std::ostream &operator<<(std::ostream &out, Block *b);

#endif
