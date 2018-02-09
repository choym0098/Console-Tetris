#include "game.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
int main(int argc, char * argv[]){
	Game g;
	bool setScript = false;
	string scriptfile = "sequence.txt";
	int startlevel = 0;
	int seed = 0;
	for(int i = 1; i < argc; i++){
		string s = argv[i];
		if(s == "-text"){
			//run text only mode>
		}else if(s == "-seed"){
			//set start level
			istringstream iss{argv[i+1]};
			iss >> seed;
			i+=1;
		}else if(s == "-scriptfile"){
			scriptfile = argv[i+1];
			setScript = true;
			i+=1;
		}else if (s == "-startlevel"){
			//set start level
			istringstream iss{argv[i+1]};
			iss >> startlevel;
			i+=1;
		}
	}
	g.setLevel(startlevel);
	if(setScript) g.setScriptFile(scriptfile);
	g.setLevelSeed(seed);
	g.playGame();

}
