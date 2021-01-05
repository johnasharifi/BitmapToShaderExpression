#pragma once

/*
* This class will take a map of ij coordinates and Pixels, and assemble a recursive structure which 
	receives queries by ij coordinates,
	determines which sub-structure to pass queries to,
	and returns a sub-structure's pixel values based on those ij coordinates
*/
class PixelMapModel
{
public:
	PixelMapModel();
	~PixelMapModel();
};

