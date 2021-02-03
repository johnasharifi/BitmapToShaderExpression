#pragma once

#include <map>
#include <set>
#include "ReadFile.h"
#include <iomanip>

/*
* This class will take a map of ij coordinates and Pixels, and assemble a recursive structure which 
	receives queries by ij coordinates,
	determines which sub-structure to pass queries to,
	and returns a sub-structure's pixel values based on those ij coordinates
*/
class PixelMapModel
{
private:
	std::vector<PixelMapModel> subModels;
	// Currently do a contained-in-box test for pixel span
	int minx, miny, maxx, maxy;
	Pixel m_Pixel;

public:
	PixelMapModel(std::map<std::pair<int, int>, Pixel> _map);
	~PixelMapModel();
	bool Contains(std::pair<int, int> ijCoord);
	Pixel GetPixel(std::pair<int, int> ijCoord);

	operator std::string();
};

