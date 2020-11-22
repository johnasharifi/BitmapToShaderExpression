#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class ReadFile
{
public:
	static std::string ReadText(const::std::string&);
	static float* imageMatrix(const::std::string&);
};

