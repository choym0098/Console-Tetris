#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "observer.h"

#include <vector>
 

class Cell;
class Board;


class TextDisplay: public Observer {
	std::vector<std::vector<char>> theDisplay;
	int row;
	int col;
	Board *b;
public:
	~TextDisplay();
	TextDisplay(int r, int c);

	// ACCESSORS AND MUTATORS
	int getRow();
	int getCol();
	void setBoard(Board *b);


	//NOTIFY
	void notify() override;
	void notify(Subject*) override;


	// I/O
	friend std::ostream &operator<<(std::ostream &out, TextDisplay &td);
};
#endif
