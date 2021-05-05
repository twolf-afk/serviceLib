#ifndef UTIL_H

#define UTIL_H

#include <string>
#include <vector>

class util {

public:

	static std::string getDateAndTime();

	static std::string getSubstringBetweenDelimiters(std::string string, std::string startDelimiter, std::string endDelimiter);

	static std::vector<std::string> splitString(std::string stringToSplit, std::string seperator);

	static std::string stringToUpperCaseString(std::string string);

	static std::vector<std::string> getFilesInDirectory(std::string directory);

	static bool stringContainsSubstring(std::string, std::string substring);

	static void saveStringAsFile(std::string string, std::string filename);

	static std::string getFile(std::string filename);

	static void createDirectory(std::string pathOfDirectory);

	static std::wstring stdStringToLPCWSTR(std::string string);

};

#endif