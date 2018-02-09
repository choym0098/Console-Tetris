#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "subject.h"
#include "cell.h"
#include "block.h"
using namespace std;

/*
---------------------------------

Constructor

---------------------------------
*/

Block::Block(char g, int levelGenerated):
  glyph{g}, levelGenerated{levelGenerated} {
  ifstream f {"blocks.txt"};
  stringstream ss;
  string s;
  char c;
  while (getline(f,s,';')) {
    ss.str(s);
    ss >> c;
    if (c == glyph) break;
  }
  int row, col;
  
  while (ss >> row) {
    ss >> col;
    CoOrd.emplace_back(pair<int,int>(row, col));
  } 
}


/*
------------------------

Accessors

------------------------
*/


char Block::getGlyph() {
  return glyph;
}

vector<pair<int, int>> Block::getCoOrd() {
  return CoOrd;
}

int Block::getScore() {
  return pow((levelGenerated + 1),2);
}

void Block::place(vector<Cell*> newLoc) {
  notifyObservers();
  observers.clear();
  vector<pair<int, int>> newcoords;
  for (auto itr = newLoc.begin(); itr != newLoc.end(); ++itr) {
    (*itr)->setBlock(this);
    newcoords.emplace_back((*itr)->getCoord());
    attach(*itr);
  }
  CoOrd = newcoords;
  
}



/*
------------------------------

Methods

------------------------------
*/


void Block::clearCoord(pair<int,int> p) {
  vector<int> index;
  for (unsigned int i = 0; i < CoOrd.size(); ++i) {
    if (CoOrd[i] == p) {
      index.emplace(index.begin(), i);
    }
  }
  for (auto j : index) {
    CoOrd.erase(CoOrd.begin() + j);
  }
}


/*
-----------------------------

I/O operation

-----------------------------
*/



ostream &operator<<(ostream &out, Block *b) {
  char l = b->getGlyph();
  Block tempblock = Block(l, 0);
  auto c = tempblock.getCoOrd();
  string e = "    ";
  vector<string> v{e,e}; 
  for (auto p : c) {
   v[p.first + 1][p.second] = l;
  }
  out << v[1] << endl << v[0] << endl;

  return out;
}
