#ifndef _COMMAND_
#define _COMMAND_
#include <string>
#include <utility>
class Command{
	std::string command_file;
	public:
		Command(std::string command_file);
		std::pair<std::string,int> getCommand(std::string input);
	
};
#endif
