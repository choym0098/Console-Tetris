#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include "observer.h"
#include "window.h"
#include <string>

class Board;

class GraphicsDisplay: public Observer {

  	Xwindow &window;

  	const int row, col;

  	int Corig=100, Rorig=6, dim=27;

  	std::string Level, Score, HiScore;

   

  public:

  	GraphicsDisplay( Xwindow &x, int r=18, int c=11 );
	void clearNextBlock();
  	~GraphicsDisplay() override;

	void notify() override;
	void notify(Board *whoNotified) override;
};





#endif

