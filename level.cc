#include "level.h"
#include <iostream>
#include <cstdlib>
#include <utility>
#include <memory>
#include <sstream>
#include "block.h"
using namespace std;

// CONSTRUCTOR ==============================================

Level::Level(int n,shared_ptr<Board>theBoard):isSequenceFile{false},isRandomFile{false},lev_num{n},seed{0},theBoard{theBoard}{}

//============================================================

// HELPER FUCTION
char Level::strToChar(string letter){
    istringstream iss(letter);
    char c;
    iss >> c;
    return c;
}



// MUTATORS  AND ACCESORS==============================================================

void Level::setCurBlock(string letter){
  auto b = make_unique<Block>(strToChar(letter),lev_num);
  theBoard->setCurBlock(b);
}
void Level::setNextBlock(string letter){
  auto b = make_unique<Block>(strToChar(letter),lev_num);
  theBoard->setNextBlock(b);
}
void Level::setSeed(int n){
	seed = n;
	srand(seed);
}
int Level::getLevNum(){
    return lev_num;
}

void Level::setSequenceFile(const string file){
        //static ifstream command_generator{file};
    if(SequenceFile.empty()){
        SequenceFile = file;
    }
    command_generator.close();
    command_generator.clear();
    try{
      command_generator.open(SequenceFile);
      isSequenceFile = true;
  }catch(ios_base::failure& e){
      isSequenceFile = false;
        //static ifstream block_generator{file};
  }

}
void Level::setRandomFile(const string file){
    if(RandomFile.empty()){
        RandomFile = file;
    }
    block_generator.close();
    block_generator.clear();
    try{
      block_generator.open(RandomFile);
      isRandomFile = true;
  }catch(ios_base::failure& e){
      isRandomFile = false;
  }

}
void Level::unSetRandomFile(){
    isRandomFile = false;
}

void Level::setBoard(shared_ptr<Board>theBoard){
    //Create the first block
    string letter = chooseBlockLetter();
    setCurBlock(letter);
    //Create Next Block
    letter = chooseBlockLetter();
    setNextBlock(letter);
}



//============================================================



// CHECK ======================================================
void Level::unSetSequenceFile(){
    isSequenceFile = false;
}

bool Level::isSequenceFileSet(){
    return isSequenceFile;
}

bool Level::isRandomFileSet(){
    return isRandomFile;
}

//============================================================


//============================================================
/*
------------------------------

OPERATIONS

------------------------------
*/

void Level::left(){
    theBoard->left();
}
void Level::right(){
    theBoard->right();
}
void Level::down(){
    theBoard->down();
}
void Level::clockwise(){
    theBoard->clockwise();
}
void Level::counterclockwise(){
    theBoard->counterclockwise();
}
void Level::drop(){
    theBoard->drop();
}
void Level::restart(){
    theBoard->restart();
}
void Level::hint(){
//        theBoard->hint();
}
void Level::makeBlock(){
    try{
        string letter = chooseBlockLetter();
        setNextBlock(letter);
    }catch(string error){
        throw error;
    }
}


void Level::play(){
    theBoard->notifyObservers();
    cout << *theBoard;
    string input;
    string command_str;
    int repeat;
    //Get input from either a file or user
    if(isSequenceFileSet()){
        command_generator >> input;
        if(command_generator.eof()) unSetSequenceFile();
    }else{  
        cin >> input; 
        if(cin.eof()) throw "eof";
    }
    //Map the input to an actual Command
    pair<string,int> result;
    result = c->getCommand(input);
    command_str = result.first;
    repeat = result.second;
    while(repeat > 0){
        if(command_str == "left"){
            this->left();
        }else if(command_str ==  "right"){
            this->right();
        }else if(command_str ==  "down"){
            this->down();
        }else if(command_str ==  "clockwise"){
            this->clockwise();
        }else if(command_str == "counterclockwise"){
            this->counterclockwise();
        }else if(command_str ==  "drop"){
            this->drop();
           // cout << "I drop the block" << endl;
            try{
                this->makeBlock(); //By default, a new block is made after being dropped
            }catch(string error){
                throw error;
            }
        }else if(command_str ==  "levelup"){
            string error = "levelUp";
            throw error;
        }else if(command_str == "leveldown"){
            string error = "levelDown";
            if(lev_num != 0) throw error;
        }else if (command_str == "sequence"){
            //Take commands from a file
            string s;
            cin >> s;
            this->setSequenceFile(s);
        }else if(command_str ==  "restart"){
            //    cout << "Executing restart" << endl;
            this->restart();
            this->makeBlock();
        }else if(command_str == "hint"){
            //    cout << "Executing hint" << endl;
            //    curLevel->hint();
        }else if(command_str == "I" ||
         command_str == "J" ||
         command_str == "L" ||
         command_str == "O" ||
         command_str == "S" ||
         command_str == "Z" ||
         command_str == "T"){
         //  cout << "Generating a block" << endl;
            this->setNextBlock(command_str);
        }else{} // Do nothing
        repeat--;
    }


}


//============================================================



Level::~Level() = default;


///////////////LEVEL0///////////////
Level0::Level0(shared_ptr<Board>theBoard):Level{0,theBoard}{
  c = make_unique<Command>("commands.txt");
    setRandomFile("sequence.txt");
}

string Level0::chooseBlockLetter(){
    string letter;
    block_generator >> letter;
    if(block_generator.peek() == EOF){
      //  cout << "We reached the end" << endl;
        setRandomFile(RandomFile);
        block_generator >> letter;
    }
    return letter;
}


//////////////LEVEL1/////////////////
Level1::Level1(shared_ptr<Board>theBoard):Level{1,theBoard}{
  c = make_unique<Command>("commands.txt");
}
string Level1::chooseBlockLetter(){
    string letter;
            //S and Z blocks are 1/12
            //Rest are 1/6 prob
            srand(time(0)); //Use current time to set the seed
            int letter_num = rand() % 12;
            if(letter_num == 0){
                letter = "S";
            }else if(letter_num == 1){
                letter = "Z";
            }else if(letter_num == 2 || letter_num == 3){
                letter = "T";
            }else if(letter_num == 4 || letter_num == 5){
                letter = "O";
            }else if(letter_num == 6 || letter_num == 7){
                letter = "L";
            }else if(letter_num == 8 || letter_num == 9){
                letter = "J";
            }else{
                letter = "I";
            }
            return letter;
        }
/////////////LEVEL2///////////////////
        Level2::Level2(shared_ptr<Board>theBoard):Level{2,theBoard}{
    c = make_unique<Command>("commands.txt");
       }
       string Level2::chooseBlockLetter(){
        string letter;

    		//All blocks are equal prob
        int letter_num = rand() % 7;

        if(letter_num == 0){
            letter = "S";
        }else if(letter_num == 1){
            letter = "Z";
        }else if(letter_num == 2){
            letter = "T";
        }else if(letter_num == 3){
            letter = "O";
        }else if(letter_num == 4){
            letter = "L";
        }else if(letter_num == 5){
            letter = "J";
        }else{
            letter = "I";
        }

        return letter;
    }
///////////LEVEL3////////////////////////
Level3::Level3(shared_ptr<Board>theBoard):Level{3,theBoard}{
      c = make_unique<Command>("commands.txt");
   }
string Level3::chooseBlockLetter(){
    string letter;
    if(isRandomFileSet()){
        block_generator >> letter;
        if(block_generator.peek() == EOF){
      //  cout << "We reached the end" << endl;
            setRandomFile(RandomFile);
            block_generator >> letter;
        }
    }else{
    		//All blocks are equal prob
    int letter_num = rand() % 9;
    if(letter_num == 0 || letter_num == 1){
        letter = "S";
    }else if(letter_num == 2 || letter_num == 3){
        letter = "Z";
    }else if(letter_num == 4){
        letter = "T";
    }else if(letter_num == 5){
        letter = "O";
    }else if(letter_num == 6){
        letter = "L";
    }else if(letter_num == 7){
        letter = "J";
    }else{
        letter = "I";
    }
}
return letter;
}

void Level3::play(){
    theBoard->notifyObservers();
    cout << *theBoard;
    string input;
    string command_str;
    int repeat;
    //Get input from either a file or user
    if(isSequenceFileSet()){
        command_generator >> input;
        if(command_generator.eof()) unSetSequenceFile();
    }else{  
        cin >> input; 
        if(cin.eof()) throw "eof";
    }
    //Map the input to an actual Command
    pair<string,int> result;
    result = c->getCommand(input);
    command_str = result.first;
    repeat = result.second;
    while(repeat > 0){
        if(command_str == "left"){
            this->left();
            this->down();
        }else if(command_str ==  "right"){
            this->right();
            this->down();
        }else if(command_str ==  "down"){
            this->down();
            this->down();
        }else if(command_str ==  "clockwise"){
            this->clockwise();
            this->down();
        }else if(command_str == "counterclockwise"){
            this->counterclockwise();
            this->down();
        }else if(command_str == "random"){
            this->unSetRandomFile();
        }else if(command_str == "norandom"){
            string file;
            cin >> file;
            this->setRandomFile(file);
        }else if(command_str ==  "drop"){
            this->drop();
            try{
                this->makeBlock(); //By default, a new block is made after being dropped
            }catch(string error){
                throw error;
            }
        }else if(command_str ==  "levelup"){
            string error = "levelUp";
            throw error;
        }else if(command_str == "leveldown"){
            string error = "levelDown";
            if(lev_num != 0) throw error;
        }else if (command_str == "sequence"){
            //Take commands from a file
            string s;
            cin >> s;
            this->setSequenceFile(s);
        }else if(command_str ==  "restart"){
            //    cout << "Executing restart" << endl;
            this->restart();
            this->makeBlock();
        }else if(command_str == "hint"){
            //    cout << "Executing hint" << endl;
            //    curLevel->hint();
        }else if(command_str == "I" ||
         command_str == "J" ||
         command_str == "L" ||
         command_str == "O" ||
         command_str == "S" ||
         command_str == "Z" ||
         command_str == "T"){
         //  cout << "Generating a block" << endl;
            this->setNextBlock(command_str);
        }
        repeat--;
    }


}
///////////LEVEL4////////////////////////
Level4::Level4(shared_ptr<Board>theBoard):Level{4,theBoard},turnsSinceClear{0}{
      c = make_unique<Command>("commands.txt");
}
string Level4::chooseBlockLetter(){
    string letter;
    if(isRandomFileSet()){
        block_generator >> letter;
        if(block_generator.peek() == EOF){
      //  cout << "We reached the end" << endl;
            setRandomFile(RandomFile);
            block_generator >> letter;
        }
    }else if(turnsSinceClear == 4){
        letter = "*";
        turnsSinceClear = 0;
    }else{
    		//All blocks are equal prob 
        int letter_num = rand() % 9;
        if(letter_num == 0 || letter_num == 1){
            letter = "S";
        }else if(letter_num == 2 || letter_num == 3){
            letter = "Z";
        }else if(letter_num == 4){
            letter = "T";
        }else if(letter_num == 5){
            letter = "O";
        }else if(letter_num == 6){
            letter = "L";
        }else if(letter_num == 7){
            letter = "J";
        }else{
            letter = "I";
        }
    }
    return letter;
}

void Level4::play(){
    theBoard->notifyObservers();
    cout << *theBoard;
    string input;
    string command_str;
    int repeat;
    oldScore = theBoard->getScore();
    //Get input from either a file or user
    if(isSequenceFileSet()){
        command_generator >> input;
        if(command_generator.eof()) unSetSequenceFile();
    }else{  
        cin >> input; 
        if(cin.eof()) throw "eof";
    }
    //Map the input to an actual Command
    pair<string,int> result;
    result = c->getCommand(input);
    command_str = result.first;
    repeat = result.second;
    while(repeat > 0){
        if(command_str == "left"){
            this->left();
            this->down();
        }else if(command_str ==  "right"){
            this->right();
            this->down();
        }else if(command_str ==  "down"){
            this->down();
            this->down();
        }else if(command_str ==  "clockwise"){
            this->clockwise();
            this->down();
        }else if(command_str == "counterclockwise"){
            this->counterclockwise();
            this->down();
        }else if(command_str == "random"){
            this->unSetRandomFile();
        }else if(command_str == "norandom"){
            string file;
            cin >> file;
            this->setRandomFile(file);
        }else if(command_str ==  "drop"){
            this->drop();
            turnsSinceClear++;
            if(oldScore != theBoard->getScore()){
                //Line was cleared
                turnsSinceClear = 0;
            }
            try{
                this->makeBlock(); //By default, a new block is made after being dropped
            }catch(string error){
                throw error;
            }
        }else if(command_str ==  "levelup"){
            string error = "levelUp";
            throw error;
        }else if(command_str == "leveldown"){
            string error = "levelDown";
            if(lev_num != 0) throw error;
        }else if (command_str == "sequence"){
            //Take commands from a file
            string s;
            cin >> s;
            this->setSequenceFile(s);
        }else if(command_str ==  "restart"){
            //    cout << "Executing restart" << endl;
            this->restart();
            this->makeBlock();
        }else if(command_str == "hint"){
            //    cout << "Executing hint" << endl;
            //    curLevel->hint();
        }else if(command_str == "I" ||
         command_str == "J" ||
         command_str == "L" ||
         command_str == "O" ||
         command_str == "S" ||
         command_str == "Z" ||
         command_str == "T"){
         //  cout << "Generating a block" << endl;
            this->setNextBlock(command_str);
        }
        repeat--;
    }


}
