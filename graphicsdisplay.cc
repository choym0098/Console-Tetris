#include "graphicsdisplay.h"
#include "cell.h"
#include "block.h"
#include "board.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay( Xwindow &x, int r, int c ):

	window{x}, row{r}, col{c} {
	int Rorig=6, Corig=100, dim=27;
	int width=1;

	window.fillRectangle(0,0,500,500,Xwindow::Black);
	window.fillRectangle(Corig, Rorig, dim*11+width, dim*18+width, Xwindow::White);

  	for(int i=0; i<=col; i++){
    	  	int r = i*dim + Corig;
    		window.fillRectangle(r, Rorig, width, dim*18, Xwindow::Black);
  	}
  	for(int i=0; i<=row; i++){
    		int c = i*dim + Rorig;
    		window.fillRectangle(Corig, c, dim*11+width, width, Xwindow::Black);
  	}
    window.drawString(5,20,"Level:", Xwindow::White);
    window.drawString(5,35,"Score:", Xwindow::White);
    window.drawString(5,50,"HiScore:", Xwindow::White);
    window.drawString(405,20,"Next Block:", Xwindow::White);
}

GraphicsDisplay::~GraphicsDisplay() { }



void GraphicsDisplay::clearNextBlock() {
  window.fillRectangle(405,40,80,40,Xwindow::Black);
}
void GraphicsDisplay::notify() {

}

void GraphicsDisplay::notify(Board *b) {
	window.fillRectangle(60, 0, 40, 70, Xwindow::Black);
	Level = to_string(b->getLevel());
	Score = to_string(b->getScore());
	HiScore = to_string(b->getHiScore());
	window.drawString(60, 20, Level, Xwindow::White);
	window.drawString(60, 35, Score, Xwindow::White);
	window.drawString(60, 50, HiScore, Xwindow::White);
	vector<vector<Cell>> &Board = b->returnBoard();
	for(unsigned int i = 0; i < Board.size(); ++i) {
		for(unsigned int j = 0; j < Board[i].size(); ++j) {
			char letter = Board[i][j].getGlyph();
			if (letter == 'I') {
				window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Orange);
			}
			else
 			if (letter == 'J') {
   				window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Yellow);
 			}
 			else
  			if (letter == 'L') {
 				window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Cyan);
  			}
  			else
  			if (letter == 'O') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Blue);
  			}
  			else
  			if (letter == 'S') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Green);
  			}
  			else
  			if (letter == 'Z') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Red);
  			}
  			else
  			if (letter == 'T') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Brown);
  			}
  			else
  			if (letter == '*') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::Black);
  			}
  			else
  			if (letter == ' ') {
    			window.fillRectangle(Corig+j*dim+1, Rorig+i*dim+1, dim-1, dim-1, Xwindow::White);			
  			}


		}
	}

	clearNextBlock();
	char glyph = b->getNextBlock()->getGlyph();
			if (glyph == 'I') {
				for(int i=0; i < 4; ++i) window.fillRectangle(405+i*20,40, 19,19,Xwindow::Orange);
			}
			else
 			if (glyph == 'J') {
   				window.fillRectangle(405,40,19,19,Xwindow::Yellow);
				for(int i=0; i<3; ++i) window.fillRectangle(405+i*20,60,19,19,Xwindow::Yellow);
 			}
 			else
  			if (glyph == 'L') {
				 window.fillRectangle(445,40,19,19,Xwindow::Cyan);
				 for(int i=0; i<3; ++i) window.fillRectangle(405+i*20,60,19,19,Xwindow::Cyan);
  			}
  			else
  			if (glyph == 'O') {
  				for(int i=0; i<2; ++i) window.fillRectangle(405+i*20,40,19,19,Xwindow::Blue);
				for(int i=0; i<2; ++i) window.fillRectangle(405+i*20,60,19,19,Xwindow::Blue);
  			}
  			else
  			if (glyph == 'S') {
    			for(int i=0; i<2; ++i) window.fillRectangle(425+i*20,40,19,19,Xwindow::Green);
   				for(int i=0; i<2; ++i) window.fillRectangle(405+i*20,60,19,19,Xwindow::Green);
  			}
  			else
  			if (glyph == 'Z') {
    			for(int i=0; i<2; ++i) window.fillRectangle(405+i*20,40,19,19,Xwindow::Red);
        		for(int i=0; i<2; ++i) window.fillRectangle(425+i*20,60,19,19,Xwindow::Red);
  			}
  			else
  			if (glyph == 'T') {
    			for(int i=0; i<3; ++i) window.fillRectangle(405+i*20,40,19,19,Xwindow::Brown);
				window.fillRectangle(425,60,19,19,Xwindow::Brown);
  			}
  			

}

