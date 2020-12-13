#pragma once
#include "IUVPixelMap.h"
#include "ReadFile.h"

/*
A class for looking up pixel colors within certain bounds.
*/
class BoxPixelMap :
	public IUVPixelMap
{
public:
	BoxPixelMap();
	~BoxPixelMap();
	Pixel Get(float uvu, float uvv);
};

