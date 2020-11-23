#include "getFileAsString.h"

#include <iostream>
#include <fstream>

std::string getFileAsString::getFile(std::string filename)
{

	std::string line;
	std::string text;

	std::ifstream file(filename);

	while (getline(file, line)) {

		text = text + line;
		std::cout << line << std::endl;
	}

	file.close();

	return text;
}