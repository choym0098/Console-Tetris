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
		void playGame();
		void setLevelSeed(int n);
		void setScriptFile(std::string file);
		void setLevel(int n = 0);
		Game(int row = 19,int col = 11);
		~Game();
};
#endif
