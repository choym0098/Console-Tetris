#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <vector>
#include <memory>
#include "cell.h"
#include "subject.h"
#include "block.h"

class Observer;
class TextDisplay;
class Level;

class Board: public Subject {
	std::vector<std::vector<Cell>> theBoard; //The Actual Board
	std::vector<std::unique_ptr<Block>> vBlock;  
	int Score = 0; // The current score of the game going on
	int Hi_Score = 0; // THe highest score ever reached in the game
	std::unique_ptr<Block> nextBlock = nullptr;
	int lvl = 0; // Current level;
	TextDisplay *td = nullptr; // The Text Displayer
	Block *tempBlock = nullptr;
protected:
	std::pair<double, double> Pivot;
public:
	int row; //including reserved lines (+3)
	int col;
	bool isItEmpty;

	~Board();
	void starCreate(Block *);
	//
	void init(int r, int c); //Initial Board 
	TextDisplay * returnTD();
	bool isBoardFull(); // check if BOARD is full
	bool isRowFull(int r); // check if the r-th row is full
	int &getScore();
	int &getHiScore();
	int &getLevel(); 

	bool isGameOver();	
	std::vector<std::vector<Cell>> &returnBoard();
	Block *getCurBlock();
	Block *getNextBlock();
	std::vector<std::pair<int, int>> rotate_findNewLocation(std::vector<std::pair<int, int>> v);	
	
	
	void setNextBlock(std::unique_ptr<Block> &bd);
	void setCurBlock(std::unique_ptr<Block> &bp); //the last item in vBlock 

	
	std::vector<Cell *> guideBlock(int r, int c, Block *b); // Let the block know where it's goning to be located
	void moveBlock(int r, int c, Block *b); //update the block (change cells in block to new cells)
	
	bool isEmpty(std::vector<std::pair<int,int>> v); //Are the cells at these coordinates empty?

	void deleteLine(); // when a line is full, delete the line;
	//Commands
	void left(); // Moves curBlock to left
	void right(); // Moves curBlock to right
	void down(); // Moves curBlock down by 1
	void drop(); // Drops curBlock to the bottom
	void restart(); // clears theBoard and remake new one
	void clockwise(); // rotates curBlock 90 degree clockwise
	void counterclockwise(); // rotates curBlock 90 degree counterclockwise
//	void hint(); // gives user the best place to put curBlock

	friend std::ostream &operator<<(std::ostream &out,  Board &bd);

	Cell* CoordsToLoc(std::pair<int,int> p);
	void deleteLineMover(int r);
};

#endif
/////////////////////////////////////////////////////////////////////////////

