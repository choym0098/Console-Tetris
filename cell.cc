#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <iostream>

#include "observer.h"
#include "block.h"
#include "cell.h"
#include "subject.h"
using namespace std;

/*
------------------------

Ctor

------------------------
*/

Cell::Cell(int row, int col):
  coord{pair<int, int>(row, col)}, block{nullptr} {}


//////////////////////////////////////////////////////////////////////////////////////////////
/*
----------------------------------

ACEESORS AND MUTATORS

----------------------------------
/*


pair<int, int> Cell::getCoord() {
  return coord;
}

Block* Cell::getBlock() {
  return block;
}

void Cell::setBlock(Block *newBlock) {
  block = newBlock;
}

char Cell::getGlyph() {
  if (block == nullptr) {
    return ' ';
  } else {
    return block->getGlyph();
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////
/*
---------------------

Methods

---------------------
*/

void Cell::notify() {
}

void Cell::notify(Subject* b) {
  notify();
}
