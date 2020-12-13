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

std::map<std::pair<int, int>, Pixel> ReadFile::TextToPixelTable(const::std::string& data) {
	std::map<std::pair<int, int>, Pixel> pixelTable;
	std::istringstream iss(data);
	std::string line;

	while (getline(iss, line)) {
		int x, y, r, g, b;

		// parse a line / string as a series of ints/floats/commas
		sscanf_s(line.c_str(), "%d,%d,%d,%d,%d", &x, &y, &r, &g, &b);

		Pixel px{ r, g, b };

		pixelTable.emplace(std::pair<int,int>(x, y), px);
	}

	return pixelTable;
}

/// Converts a string into a collection of pixels and pixel counts. Similar to a freq table
std::map<Pixel, int> ReadFile::TextToSparsePixels(const::std::string& data)
{
	std::map<Pixel, int> pixelCounts;
	std::istringstream iss(data);
	std::string line;

	while (getline(iss, line)) {
		// create vars for parsing
		int x, y, r, g, b;

		// parse a line / string as a series of ints/floats/commas
		sscanf_s(line.c_str(), "%d,%d,%d,%d,%d", &x, &y, &r, &g, &b);

		Pixel px { r, g, b };

		pixelCounts[px] += 1;
	}

	return pixelCounts;
}
