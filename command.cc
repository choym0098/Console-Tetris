#include "command.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
/*
----------------------------------

CONSTRUCTOR

----------------------------------
/*

Command::Command(string command_file):command_file{command_file}{}
pair<string,int> Command::getCommand(string input){
	 //Intializatiion streams
     string command_str;
     istringstream ss(input.substr(0,1));
     //Check if first char is a number
     int start = 0;
     int repeat;
     if(ss >> repeat){
     	start = 1;
     }else{
        repeat = 1;
     }
     //Start looking for the command
     string word;
     int max = input.size();
     for(int i = 1; i <= max; i++){
     	//Make temp list
        vector<string> commands_vec;
        ifstream cf(command_file);
        while(!cf.eof()){
        	cf >> word;
            //Check if the substrings match.
            string letter = word.substr(0,i);
            if(letter == input.substr(start,i)){
            	commands_vec.emplace_back(word);
            }
        }
        //After iterating through the file, check to see if there is only one match
        if(commands_vec.size() == 1){
        	command_str = commands_vec[0];
            break;
          }else{
          	for(auto &n:commands_vec){
            if(n.size() == input.size()) command_str = n;
          	}
          }
        }
        return pair<string,int>(command_str,repeat);
}
