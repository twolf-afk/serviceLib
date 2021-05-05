#include "util.h"

#include "logUtil.h"

#include <windows.h>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

std::string util::getDateAndTime() {

	time_t now = time(0);
	std::tm timeStruct{};
	localtime_s(&timeStruct, &now);
	char buffer[64];

	return
	{
		buffer, std::strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &timeStruct)
	};
}

std::vector<std::string> util::splitString(std::string stringToSplit, std::string seperator) {

	std::vector<std::string> stringVector;

	size_t position = 0;
	std::string stringPart;
	while ((position = stringToSplit.find(seperator)) != std::string::npos) {
		stringPart = stringToSplit.substr(0, position);
		stringVector.push_back(stringPart);
		stringToSplit.erase(0, position + seperator.length());
	}

	stringVector.push_back(stringToSplit);

	return stringVector;
}

std::string util::getSubstringBetweenDelimiters(std::string string, std::string startDelimiter, std::string endDelimiter) {
	
	size_t from = string.find(startDelimiter) + startDelimiter.length();
	size_t until = string.find(endDelimiter) - from;

	std::string substring = string.substr(from, until);

	return substring;
}

std::string util::stringToUpperCaseString(std::string string) {
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
	return string;
}

std::vector<std::string> util::getFilesInDirectory(std::string directory) {

	logUtil::writeLogMessageToConsoleAndFile("info", typeid(util).name(), __LINE__, "Directory: " + directory);

	std::vector<std::string> files;

	for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {

		std::string file = entry.path().string().c_str();

		std::vector<std::string> fileParts = util::splitString(file, "/");

		if (util::stringContainsSubstring(directory, "processes")) {
			if (util::stringContainsSubstring(fileParts[fileParts.size() - 1], ".xml")) {
				std::string fileName = util::splitString(fileParts[fileParts.size() - 1], "\\")[1];

				files.push_back(fileName);
			}
		} else {
			files.push_back(fileParts[fileParts.size() - 1]);
		}

	}

	return files;
}

bool util::stringContainsSubstring(std::string string, std::string substring) {

	if (string.find(substring) != std::string::npos) {
		return true;
	} else {
		return false;
	}
}

void util::saveStringAsFile(std::string string, std::string filename) {

	if (std::ifstream(filename.c_str())) {
		remove(filename.c_str());
	}

	std::ofstream file;
	file.open(filename, std::ios_base::app);

	file << string;
	file.close();

}

std::string util::getFile(std::string filename) {

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

void util::createDirectory(std::string pathOfDirectory) {

	std::wstring wString = stdStringToLPCWSTR(pathOfDirectory);
	LPCWSTR lpcwstrString = wString.c_str();

	if (CreateDirectory(lpcwstrString, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		logUtil::writeLogMessageToConsoleAndFile("info", typeid(util).name(), __LINE__, "Success");
	} else {
		logUtil::writeLogMessageToConsoleAndFile("info", typeid(util).name(), __LINE__, "Failed");
	}
}

std::wstring util::stdStringToLPCWSTR(std::string string) {
	
	int length;
	int stringLength = (int)string.length() + 1;
	length = MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, 0, 0);
	wchar_t* buffer = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, buffer, length);
	std::wstring wString(buffer);
	delete[] buffer;

	return wString;
}