#include "pch.h"
#include "ReadFile.h"

/// Reads a resource file in as a string, returns the string
std::string ReadFile::ReadText(const::std::string& filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;

	// ensure file terminates with blank newline
	while (getline(stream, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

float * ReadFile::imageMatrix(const::std::string& data)
{
	std::cout << "convert to image matrix" << std::endl;
	return nullptr;
}
