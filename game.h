#ifndef _GAME_
#define _GAME_
#include <memory>
#include "level.h"
#include "board.h"
#include <string>
class Game{
	int row,col;
	std::shared_ptr<Board> theBoard;
	Level * curLevel;
	public:
		// OPERATION

		void playGame();
		

		// MUTATORS

		void setLevelSeed(int n);
		void setScriptFile(std::string file);
		void setLevel(int n = 0);


		// CONSTRUCTORS

		Game(int row = 19,int col = 11);


		// DESTRUCTORS

		~Game();
};
#endif
