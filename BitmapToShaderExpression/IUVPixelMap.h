#pragma once

#include "ReadFile.h"

class IUVPixelMap
{
public:
	IUVPixelMap();
	virtual Pixel Get(float uvu, float uvv) = 0;
	~IUVPixelMap();
};

