#include <iostream>
#include <string>

void Log(const char* message) // const char* message is a parameter.
{
	std::cout << message << '\n'; // Think of the << operator like a function.
}

void Log(std::string message) // const char* message is a parameter.
{
	std::cout << message << '\n'; // Think of the << operator like a function.
}