#include "util.h"

#include "logUtil.h"

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

	size_t pos = 0;
	std::string token;
	while ((pos = stringToSplit.find(seperator)) != std::string::npos) {
		token = stringToSplit.substr(0, pos);
		stringVector.push_back(token);
		stringToSplit.erase(0, pos + seperator.length());
	}

	return stringVector;
}

std::string util::stringToUpperCaseString(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
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