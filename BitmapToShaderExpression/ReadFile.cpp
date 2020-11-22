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

/// Converts a string into a collection of pixels and pixel counts. Similar to a freq table
std::map<Pixel, int> ReadFile::TextToSparsePixels(const::std::string& data)
{
	std::map<Pixel, int> pixelCounts;
	std::istringstream iss(data);
	std::string line;

	while (getline(iss, line)) {
		// create vars for parsing
		int x, y;
		float r, g, b;

		// parse a line / string as a series of ints/floats/commas
		sscanf_s(line.c_str(), "%d,%d,%f,%f,%f", &x, &y, &r, &g, &b);

		Pixel px { r, g, b };

		pixelCounts[px] += 1;
	}

	return pixelCounts;
}
