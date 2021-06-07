#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct Pixel {
	int r, g, b;
	const int pixelConverter = 255;

	// Have to define comparison op so that pixels can be sorted in map
	bool operator < (const Pixel& other) const {
		return r < other.r ||
			r == other.r && g < other.g ||
			r == other.r && g == other.g && b < other.b;
	}

	operator std::string() {
		std::ostringstream stringStream;
		stringStream << "r" << r << " g" << g << " b" << b;
		return stringStream.str();
	}

	Pixel& operator=(const Pixel& rhs) {
		if (this == &rhs) return *this;
		// operator= should
		// escape case where ptr to this == address of rhs
		// take a const address of original value (right hand value)
		// return left hand value so that we can do ops like x = y = z
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		return *this;
	}

	bool operator ==(const Pixel& right) {
		return r == right.r && b == right.b && g == right.g;
	}

	/*
	Deprecate &=, now use equality operator
	*/
	[[deprecated]]
	bool operator &=(const Pixel& right) {
		return *this == right;
	}
};

class ReadFile
{
public:
	static std::string ReadText(const::std::string&);
	static std::map<Pixel, int> TextToSparsePixels(const::std::string&);
	static std::map<std::pair<int, int>, Pixel> TextToPixelTable(const::std::string& data);
};
