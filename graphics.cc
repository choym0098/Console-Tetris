
#include "window.h"

#include "graphics.h"

#include "cell.h"

#include "block.h"

#include "board.h"

using namespace std;



//////////////////////////////////////////////////////////////////////////////////////////////
/*
----------------------------------

CONSTRUCTOR

----------------------------------
/*

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


// DESTRUCTOR=================================================
GraphicsDisplay::~GraphicsDisplay() { }

==============================================================

// RESET THE BOARD TO TOTAL CLEARANCE ===========================
void GraphicsDisplay::clearNext() {

  window.fillRectangle(405,40,80,40,Xwindow::Black);

}
==============================================================



// NOTIFY======================================================
void GraphicsDisplay::notify( const Cell &c ) {


}



void GraphicsDisplay::notify( const Block &b ) {


}

void GraphicsDisplay::notify( const Board &b ) {
  window.drawString(60,50,hiScore, Xwindow::White);

}

==============================================================
