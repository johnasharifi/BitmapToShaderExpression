#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct Pixel {
	float r, g, b;
	const int pixelConverter = 255;

	// Have to define comparison op so that pixels can be sorted in map
	bool operator < (const Pixel other) const {
		return r < other.r && g < other.g && b < other.b;
	}

	operator std::string() {
		std::ostringstream stringStream;
		stringStream << "r" << r << " g" << g << " b" << b;
		return stringStream.str();
	}
};

class ReadFile
{
public:
	static std::string ReadText(const::std::string&);
	static std::map<Pixel, int> TextToSparsePixels(const::std::string&);
	static std::map<std::pair<int, int>, Pixel> TextToPixelTable(const::std::string& data);
};
