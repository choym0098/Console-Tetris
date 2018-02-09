#include "textdisplay.h"
#include "cell.h"
#include "board.h"
using namespace std;

// DTOR
TextDisplay::~TextDisplay() {
	delete b;
}

// CTOR
TextDisplay::TextDisplay(int r, int c): row{r}, col{c} {
	for(int i=0; i < r; ++i) {
		vector<char> row;
		for(int j = 0; j < c; ++j) {
			row.emplace_back(' ');
		}
		theDisplay.emplace_back(row);
	}
}

// MUTATOR
void TextDisplay::setBoard(Board *s) {
	b = s;
}

// ACCESORS===================================================
int TextDisplay::getRow() {
	return row;
}
int TextDisplay::getCol() {
	return col;
}

==============================================================


// NOTIFY======================================================

void TextDisplay::notify() {
	vector<vector<Cell>> temp = b->returnBoard();
	for(int i=0; i < row; ++i) {
		for(int j = 0; j < col; ++ j) {
			char c = temp[i][j].getGlyph();
			theDisplay[i][j] = c;
		}
	}
}

void TextDisplay::notify(Subject* b) {
  notify();
}
==============================================================


ostream &operator<<(std::ostream &out, TextDisplay &td) {

	//The Acutal Board : 15 rows, 11 cols
    
    for(int i = td.getRow() - 1; i > -1; --i) {
        for(int j = 0; j < td.getCol(); ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}

