#ifndef _GRAPHICSDISPLAY_H_

#define _GRAPHICSDISPLAY_H_

#include "observer.h"

#include "window.h"

#include <string>



class Cell;

class Block;

class Board;



class GraphicsDisplay {

  	Xwindow &window;

  	const int row, col;

  	int Corig=100, Rorig=6, dim=27;

  	std::string level, score, hiScore;

 

    void clearNext();

 

  public:

  	GraphicsDisplay( Xwindow &x, int r=18, int c=11 );

  	~GraphicsDisplay();



  	void notify( const Cell &c );

  	void notify( const Block &c );

  	void notify( const Board &c );

  	



};





#endif
