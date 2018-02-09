#ifndef _LEVEL_
#define _LEVEL_
#include <memory>
#include <fstream>
#include "board.h"
#include "block.h"
#include "command.h"
class Level{
protected:
  std::unique_ptr<Command> c;
   bool isSequenceFile;
   bool isRandomFile;
   int lev_num;
   int seed;
   std::string RandomFile;
   std::string SequenceFile;
   std::ifstream block_generator;
   std::ifstream command_generator;
        //Helper Functions
   char strToChar(std::string letter);
   void setCurBlock(std::string letter);
   void setNextBlock(std::string letter);
        //Methods for Sequence Command
   void setSequenceFile(const std::string file);
   void unSetSequenceFile();
   bool isSequenceFileSet();
        //Methods for Random Block Generation
   void unSetRandomFile();
   bool isRandomFileSet();
        //Commands that affect Board State
   virtual void left();
   virtual void right();
   virtual void down();
   virtual void clockwise();
   virtual void counterclockwise();
   virtual void drop();
   virtual void restart();
   virtual void hint();
public:
    std::shared_ptr<Board> theBoard;
    Level(int n,std::shared_ptr<Board>theBoard); //Constructor
    //Accessor Methods
    int getLevNum();
    void setSeed(int n);
    void setRandomFile(const std::string file);
    //GamePlay Methods
    virtual void makeBlock(); //Make the block, optionally can be overriden
    virtual void setBoard(std::shared_ptr<Board>theBoard);
    virtual void play(); //Chooses which command to run based off input
    virtual std::string chooseBlockLetter()= 0;
    //Constructor and Destructor
    virtual ~Level();
};

class Level0: public Level{
    public:
        Level0(std::shared_ptr<Board>theBoard);
        std::string chooseBlockLetter()override;
};

class Level1:public Level{
    public:
        Level1(std::shared_ptr<Board>theBoard);
        std::string chooseBlockLetter()override;
};

class Level2:public Level{
  public:
    Level2(std::shared_ptr<Board>theBoard);
    std::string chooseBlockLetter()override;  

};

class Level3:public Level{
  public:
    Level3(std::shared_ptr<Board>theBoard);
    std::string chooseBlockLetter()override; 
    void play()override; 

};
class Level4:public Level{
  int turnsSinceClear;

  public:
    int oldScore;
    Level4(std::shared_ptr<Board>theBoard);
    std::string chooseBlockLetter()override; 
    void play()override; 

};

#endif
