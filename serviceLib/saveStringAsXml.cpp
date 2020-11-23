#include "saveStringAsXml.h"

#include <fstream>

void saveStringAsXml::saveStringAsFile(std::string string, std::string filename)
{

	std::ifstream checkLogFile(filename.c_str());

	std::ofstream logFile;
	logFile.open(filename, std::ios_base::app);

	logFile << string;
	logFile.close();

}
