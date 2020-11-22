#pragma once

#include <string>
#include <iostream>

class ReadFile
{
public:
	static std::string ReadCSV(const::std::string&);
	static float* imageMatrix(const::std::string&);
};

