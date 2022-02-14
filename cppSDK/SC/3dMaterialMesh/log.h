#ifndef LOG_H
#define LOG_H
#include <string>
#include <iostream>
const int wall = 1;
	//0 error 1 warning 2 event 3 something
void _log(int level, std::string a)
{
	if (level < wall)
		std::cout << a << std::endl;
}

#endif LOG_H