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
	void setBoard(Board *b);
	~TextDisplay();
	TextDisplay(int r, int c);
	int getRow();
	int getCol();
	void notify() override;
	void notify(Subject*) override;
	friend std::ostream &operator<<(std::ostream &out, TextDisplay &td);
};
#endif
