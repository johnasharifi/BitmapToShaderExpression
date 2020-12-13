#pragma once

#include "ReadFile.h"

/*
An interface base class whose implementers will abstractly support getting a pixel when given a UV coordinate.
*/
class IUVPixelMap
{
public:
	IUVPixelMap();
	
	/*
	The IUVPixelMap will support getting a pixel when given a uv coordinate.
	*/
	virtual Pixel Get(float uvu, float uvv) = 0;

	~IUVPixelMap();
};

