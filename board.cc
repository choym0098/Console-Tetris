#include "textdisplay.h"
#include <utility>
#include "board.h"
#include "cell.h"
#include "block.h"
#include <algorithm>
#include "level.h"
#include <cmath>
#include <memory>
using namespace std;


void Board::starCreate(Block *b) {
	bool empty = false;
	int newRow = 0;
	for( int i = 0; i < row - 3; ++i) {
		if(theBoard[i][col / 2].getGlyph() == ' ') {
			empty = true;
			break;
		}
		++newRow;
	}
	vector<Cell *> v;
	v.emplace_back(&theBoard[newRow][col / 2]); 	
	if(empty) {
		b->place(v);
	}
}


Board::~Board() {
}

ostream &operator<<(ostream &out, Board &bd) {
	out << "Level:      " << bd.getLevel() << endl;
	out << "Score:      " << bd.getScore() << endl;
	out << "Hi Score:  " << bd.getHiScore() << endl;
	out << "-----------" << endl;
	out << *(bd.td);
	out << "-----------" << endl;
	out << "Next:" << endl;
	out << bd.getNextBlock() << endl;
	return out;
}

vector<pair<int,int>> findCorners(vector<pair<int,int>> v) { //1st = bottom left, 2nd = bottom-right, 3rd = top-left, 4th = top-right
        int minRow=100;
        int minCol=100;
        int maxCol=0;
        int maxRow=0;
        unsigned int size = v.size();
        vector<pair<int,int>> Corners;
        //get minRow
        for(unsigned int i = 0; i<size; ++i) {
                if(minRow > v[i].first) {
                        minRow = v[i].first;
                }
        }
        //get maxRow
        for(unsigned int i = 0; i<size; ++i) {
                if(maxRow < v[i].first) {
                        maxRow = v[i].first;
                }
        }
        //get minCol
        for(unsigned int i = 0; i<size; ++i) {
                if(minCol > v[i].second) {
                        minCol = v[i].second;
                }
        }
        //find maxCol
        for(unsigned int i = 0; i<size; ++i) {
                if(maxCol < v[i].second) {
                        maxCol = v[i].second;
                }
        }
        pair<int, int> v1 = pair<int, int>(minRow, minCol);
        pair<int, int> v2 = pair<int, int>(minRow, maxCol);
        Corners.emplace_back(v1);
        Corners.emplace_back(v2);

        pair<int, int> v3 = pair<int, int>(maxRow, minCol);
        pair<int, int> v4 = pair<int, int>(maxRow, maxCol);
        Corners.emplace_back(v3);
        Corners.emplace_back(v4);

        return Corners;
}

bool Board::isGameOver() {
	if(isItEmpty) {
		return false;
	}
	return true;
}



int findSide(vector<pair<int, int>> v) {
        int side = 0;
        int width = v[1].second - v[0].second;
        int height = v[3].first - v[0].first;
        if (width >= height) {
                side = width;
        } else {
                side = height;
        }
        return side;
}

pair<double, double> findPivot(vector<pair<int, int>> v) {
	int side = findSide(v);
        pair<double, double> d;
        if (side == 2) {
                d.first = v[0].first + 1;
                d.second = v[0].second + 1;
        } else if (side == 3) { // I block
                d.first = v[0].first + 1.5;
                d.second = v[0].second + 1.5;
        } else if (side == 1) { // O block
		d.first = v[0].first + 0.5;
		d.second = v[0].second + 0.5;
        }
        return d;
}

vector<pair<int, int>> Board::rotate_findNewLocation(vector<pair<int, int>> v) {
        vector<pair<int, int>> corners = findCorners(v);
	pair<double, double> pivot = this->Pivot;
        double p1 = pivot.first;
        double p2 = pivot.second;
        int v1;
        int v2;
        pair<int, int> newCoord;
        vector<pair<int, int>> newLocation;
        for(unsigned int i = 0; i < v.size(); ++i) {
                v1 = v[i].first;
                v2 = v[i].second;
                newCoord.first = p1 - p2 + v2;
                newCoord.second = p1 + p2 - v1;
                newLocation.emplace_back(newCoord);
        }
        return newLocation;
}


void Board::init(int r, int c) {
	td = new TextDisplay{r, c};
	this->attach(td);
	row = r;
	col = c;
	//assign remaining ptrs to corresponding objects;
	vector<unique_ptr<Block>> vB;
	vB.emplace_back(nullptr);


	//////////////////////////////////////////////////

	//Initialize theBoard;
	for (int i = 0; i < r; ++i) {
		vector<Cell> row;
		for(int j = 0; j < c; ++j) {
			row.emplace_back(i, j);
		}
		theBoard.emplace_back(row);
	}

	td->setBoard(this);
}


vector<vector<Cell>> &Board::returnBoard() {
	return theBoard;
}

bool Board::isBoardFull() {
	for(int i = 0; i < row - 3; ++i) {
		if (isRowFull(i) == false) {
			return false;
		}
	}
	return true;
} 

bool Board::isRowFull(int r) {
	for(int i=0; i < col; ++i) {
		if(theBoard[r][i].getGlyph() == ' ') {
			return false;
		}
	}
	return true;
}

int &Board::getScore() {
	return Score;
}
int &Board::getHiScore() {
	return Hi_Score;
}
int &Board::getLevel() {
	return lvl;
}

Block *Board::getCurBlock() {
	int size = vBlock.size();
	if (size == 0) {
		return nullptr;
	} else {
	  return vBlock[size-1].get();
	}
}
Block *Board::getNextBlock() {
  return nextBlock.get();
}

void Board::setNextBlock(unique_ptr<Block> &bd) {
  swap(nextBlock, bd);
}
//Not sure if we make the Board have a level


void Board::setCurBlock(unique_ptr<Block> &bp) {
  Block *b = bp.get();
  auto newcoords = b->getCoOrd();
	vector<Cell*> v;
	for (unsigned int i =0; i < newcoords.size(); ++i) {
		newcoords[i].first += 15;
		v.emplace_back(&theBoard[newcoords[i].first][newcoords[i].second]);
	}
	
	bool isItEmpty=true;
	for(unsigned int i = 0; i < newcoords.size(); ++i) {
		if(theBoard[newcoords[i].first][newcoords[i].second].getGlyph() != ' ') {
			isItEmpty = false;
		}
	}
	if(isItEmpty) {
		b->place(v);
		vBlock.emplace_back(nullptr);
		swap(vBlock.back(), bp);
		Pivot = findPivot(findCorners(vBlock[vBlock.size() - 1]->getCoOrd()));
	} else {
		restart();
	}
}


vector<Cell *> Board::guideBlock(int r, int c, Block *b) {
	vector<pair<int, int>> vCoord = b->getCoOrd();
	vector<Cell *> newCells;
	for(unsigned int i =0; i < vCoord.size(); ++i) {
		newCells.emplace_back(&theBoard[vCoord[i].first + r][vCoord[i].second + c]);
	}
	return newCells;
}
bool helpEmpty(pair<int, int> p, vector<pair<int, int>> v) {
	for(unsigned int i = 0; i < v.size(); ++i) {
		if (p.first == v[i].first && p.second == v[i].second) {
			return true;
		}
	}
	return false;
}

bool Board::isEmpty(vector<pair<int,int>> v) {
	vector<pair<int, int>> curCoord = vBlock[vBlock.size() - 1]->getCoOrd();
	for(unsigned int i = 0; i < v.size(); ++i) {
		if (v[i].first < 0 || v[i].second < 0 || v[i].second > 10) {
			return false;
		}
		if (helpEmpty(v[i], curCoord)) {
		} else {
			if(theBoard[v[i].first][v[i].second].getGlyph() != ' ') {
				return false;
			}
		}
	}
	return true;
}

void Board::moveBlock(int r, int c, Block *b) {
	vector<pair<int, int>> vCoord= b->getCoOrd();

	for(unsigned int i = 0; i < vCoord.size(); ++i) {
		vCoord[i].first += r;
		vCoord[i].second += c;
	}
	if(isEmpty(vCoord)) {
		b->place(guideBlock(r, c, b));		
	}

}



void Board::left() {
  this->moveBlock(0, -1, getCurBlock());
  char letter = getCurBlock()->getGlyph();
	if (letter == 'I' || letter == 'O') {
		if(Pivot.second > 0) {
			--Pivot.second;
		}
	} else {
		if(Pivot.second > 1) {
			--Pivot.second;
		}
	}
}

void Board::right() {
  this->moveBlock(0, 1, getCurBlock());
  char letter = getCurBlock()->getGlyph();
        if (letter == 'I') {
		if(Pivot.second < 8) {
			++Pivot.second;
		}
	} else {
		if(Pivot.second < 10) {
			++Pivot.second;
		}
	}
}

void Board::down() {
  this->moveBlock(-1, 0, getCurBlock());
  char letter = getCurBlock()->getGlyph();
        if (letter == 'I' || letter == 'O') {	
		if(Pivot.first > 0) {
			--Pivot.first;
		}
	} else {
		if(Pivot.first > 1)  {
			--Pivot.first;
		}
	}
}

void Board::drop() {
  vector<pair<int, int>> vCoord = getCurBlock()->getCoOrd();
	for(unsigned int i = 0; i < vCoord.size(); ++i) {
		vCoord[i].first += -1;
	}
	while(isEmpty(vCoord)) {
		this->down();
		for(unsigned int i = 0; i < vCoord.size(); ++i) {
			--vCoord[i].first;
		}
	}
	this->deleteLine();
	this->setCurBlock(nextBlock);
}

void Board::restart() {
	if(getHiScore() < getScore()) {
		getHiScore() = getScore();
	}
	getScore() = 0;
	theBoard.clear();
	this->init(19, 11);
	vBlock.clear();
	setCurBlock(nextBlock);
}

Cell* Board::CoordsToLoc(pair<int, int> p) {
  return (&(theBoard.at(p.first)).at(p.second));
}

void Board::deleteLineMover(int r) {
  for (auto itr = vBlock.begin(); itr != vBlock.end(); ++itr) {
    Block *b = (*itr).get();
    auto loc = b->getCoOrd();
    vector<Cell*> target;
    for (auto v : loc) {
      if (v.first != r) {
	target.emplace_back(CoordsToLoc(v));
      } else {
	target.emplace_back(CoordsToLoc(pair<int,int>{v.first-1, v.second}));
      }
    }
    b->place(target);
  }
}

void Board::deleteLine() {
  int linesCleared = 0;
  for (int cur = theBoard.size() - 2; cur >= 0; --cur) {
    if (isRowFull(cur)) {
      for (auto c : theBoard[cur]) {
	(c.getBlock())->clearCoord(c.getCoord());
	c.notify(); // This with the above line clears the cell
      }
      for (unsigned int i = cur; i < theBoard.size()-1; ++i) {
	deleteLineMover(i+1);
      }
      linesCleared++;
    }
  }

  //Score when lines get deleted
  if(linesCleared > 0) {
    int score = pow((linesCleared + getLevel()),2);
    vector<int> index;
    //Score when the whole blocks are gone
    for (unsigned int j = 0; j < vBlock.size(); ++j) {
      if (vBlock[j]->getCoOrd().empty()) {
        index.emplace_back(j);
        score = score + (vBlock[j])->getScore();
      }
    }

    for (auto ritr = index.rbegin(); ritr != index.rend(); ++ritr) {
      vBlock.erase(vBlock.begin() + *ritr);
    }
    this->getScore() += score;
  }
}


void Board::clockwise() {
	this->counterclockwise();
	this->counterclockwise();
	this->counterclockwise();

}

void Board::counterclockwise() {
  vector<pair<int, int>> Coord = getCurBlock()->getCoOrd();
        vector<pair<int, int>> newCoord = rotate_findNewLocation(Coord);
        vector<Cell *> newCells;
        for(unsigned int i = 0; i < Coord.size(); ++i) {
                newCells.emplace_back(&theBoard[newCoord[i].first][newCoord[i].second]);
        }
        if(isEmpty(newCoord)) {
	  getCurBlock()->place(newCells);
        }



}

