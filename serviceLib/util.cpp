#include "util.h"

#include "logUtil.h"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include <ctime>
#include <filesystem>

std::string util::getDateAndTime()
{
	time_t now = time(0);
	std::tm timeStruct{};
	localtime_s(&timeStruct, &now);
	char buffer[64];
	return
	{
		buffer, std::strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &timeStruct)
	};
}

std::vector<std::string> util::splitString(std::string stringToSplit, std::string seperator)
{
	std::vector<std::string> stringVector;
	boost::split(stringVector, stringToSplit, boost::is_any_of(seperator));
	return stringVector;
}

std::string util::stringToUpperCaseString(std::string string)
{
	boost::to_upper(string);
	return string;
}

std::string util::boolToString(bool value)
{
	if (value)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

char* util::stringToChar(std::string string)
{

	rsize_t lengthOfChar = string.length() + 1;
	char* Char = new char[lengthOfChar];
	strcpy_s(Char, lengthOfChar, string.c_str());
	return Char;
}

std::vector<std::string> util::getFilesInDirectory(std::string directory)
{
	logUtil::writeLogMessageToConsoleAndFile("info", typeid(util).name(), __LINE__, "Directory: " + directory);

	std::vector<std::string> files;

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{

		std::string file = entry.path().string().c_str();

		std::vector<std::string> fileParts = util::splitString(file, "'/");

		files.push_back(fileParts[fileParts.size()-1]);

	}

	return files;
}