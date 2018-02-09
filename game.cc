#include "game.h"
#include <memory>
#include <string>
using namespace std;
Game::Game(int row,int col):row{row},col{col}{
	theBoard = make_shared<Board>(); // shared pointer
	theBoard->init(row,col); //Makes 19 by 11 board

}
void Game::playGame(){
	curLevel->setBoard(theBoard);	
	while(true){
		try{
			curLevel->play();
		}catch(string errorAction){
			if(errorAction == "levelUp"){
				//Go up a level
				if(curLevel->getLevNum() == 0){
					Level * temp = curLevel;
					curLevel = new Level1(theBoard);
					delete temp;
				}else if(curLevel->getLevNum() == 1){
					Level * temp = curLevel;
					curLevel = new Level2(theBoard);
					delete temp;
				}else if(curLevel->getLevNum() == 2){
					Level * temp = curLevel;
					curLevel = new Level3(theBoard);
					 delete temp;
				}else if(curLevel->getLevNum() == 3){
					Level * temp = curLevel;
					curLevel = new Level4(theBoard);
					delete temp;
				}
				theBoard->getLevel() = curLevel->getLevNum(); 
			}else if(errorAction == "levelDown"){
				//Go down a level
				if(curLevel->getLevNum() == 1){
					Level * temp = curLevel;
					curLevel = new Level0(theBoard);
					delete temp;
				}else if(curLevel->getLevNum() == 2){
					Level * temp = curLevel;
					curLevel = new Level1(theBoard);
					delete temp;
				}else if(curLevel->getLevNum() == 3){
					Level * temp = curLevel;
					curLevel = new Level2(theBoard);
					delete temp;
				}else if(curLevel->getLevNum() == 4){
					Level * temp = curLevel;
					curLevel = new Level3(theBoard);
					delete temp;
				}
				theBoard->getLevel() = curLevel->getLevNum();
			}else{
				cout << errorAction << endl;
				break;
			}
	
		}
	}

}
void Game::setLevelSeed(int n){
	curLevel->setSeed(n);
}
void Game::setScriptFile(string file){
	curLevel->setRandomFile(file);
}
void Game::setLevel(int n){
	if(n == 0){
		curLevel = new Level0(theBoard); // switch to unique ptr
	}else if(n == 1){
		curLevel = new Level1(theBoard); // switch to unique ptr
	}else if(n == 2){
		curLevel = new Level2(theBoard); // switch to unique ptr
	}else if(n == 3){
		curLevel = new Level3(theBoard); // switch to unique ptr
	}else if(n == 4){
		curLevel = new Level4(theBoard); // switch to unique ptr
	}
	theBoard->getLevel() = curLevel->getLevNum(); 
}
Game::~Game(){
	delete curLevel;
}
