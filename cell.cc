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

Cell::Cell(int row, int col):
  coord{pair<int, int>(row, col)}, block{nullptr} {}

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

void Cell::notify() {
//  cout << "Cell Notified: " << coord.first << ", " << coord.second << endl;
  //auto bCoord = block->getCoOrd();
  //auto p = find(bCoord.begin(), bCoord.end(), coord);
  //  if (p == bCoord.end()) {
    //    block->detach(this);
    setBlock(nullptr);
    //}
}

void Cell::notify(Subject* b) {
  notify();
}
